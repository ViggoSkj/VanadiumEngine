#pragma once


struct IdIndexLookup
{
	IdIndexLookup() = default;
	IdIndexLookup(unsigned int id, unsigned int index)
		: Id(id), Index(index) {
	};

	unsigned int Id = 0;
	unsigned int Index = 0;
};

class IdIndexMap
{
public:
	void InsertLookup(unsigned int id, unsigned int index);
	unsigned int FindLookupIndex(unsigned int id);
	unsigned int GetIndex(unsigned int id);
	unsigned int MarkRemoved(unsigned int id);
	void Sort();
	void Flush();
	void UpdateIndex(unsigned int id, unsigned int newIndex);

	std::size_t EmptySlotCount() const { return EmptySlots.size(); };

private:
	std::vector<IdIndexLookup> Lookups;
	std::vector<unsigned int> EmptySlots;
};