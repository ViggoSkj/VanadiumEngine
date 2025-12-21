import os
import re
import sys

ROOT_DIR = sys.argv[1] if len(sys.argv) > 1 else "."
EXTENSIONS = (".c", ".cpp", ".h", ".hpp")

# Matches glFunctionName(
GL_CALL_REGEX = re.compile(r'\bgl[A-Z][A-Za-z0-9_]*\s*\(')

# Matches GL_CALL( glFunctionName(
WRAPPED_REGEX = re.compile(r'\bGL_CHECK\s*\(\s*gl[A-Z][A-Za-z0-9_]*\s*\(')

# ---------- SCAN ----------
def scan_file(path):
    violations = []
    in_block_comment = False

    try:
        with open(path, "r", encoding="utf-8", errors="ignore") as f:
            for lineno, line in enumerate(f, 1):
                original_line = line.rstrip()

                # Handle block comments (simple, line-based)
                if in_block_comment:
                    if "*/" in line:
                        in_block_comment = False
                    continue

                if "/*" in line:
                    if "*/" not in line:
                        in_block_comment = True
                    continue

                # Remove inline // comments
                line = re.sub(r'//.*', '', line)

                # Skip empty or whitespace-only lines
                if not line.strip():
                    continue

                # Detect GL calls anywhere in the line (indentation ok)
                if GL_CALL_REGEX.search(line):
                    if not WRAPPED_REGEX.search(line):
                        violations.append((lineno, original_line))

    except Exception as e:
        print(f"[ERROR] Could not read {path}: {e}")

    return violations


def scan_directory(root):
    results = []
    for dirpath, _, filenames in os.walk(root):
        for file in filenames:
            if file.endswith(EXTENSIONS):
                full_path = os.path.join(dirpath, file)
                for lineno, line in scan_file(full_path):
                    results.append((full_path, lineno, line))
    return results


# ---------- MAIN ----------
if __name__ == "__main__":
    findings = scan_directory(ROOT_DIR)

    if not findings:
        print("✅ No unwrapped OpenGL calls found.")
        sys.exit(0)

    print("❌ Unwrapped OpenGL calls found:\n")
    for path, lineno, line in findings:
        print(f"{path}:{lineno}")
        print(f"    {line}\n")

    print(f"Total violations: {len(findings)}")
    sys.exit(1)
