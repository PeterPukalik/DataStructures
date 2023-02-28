#pragma once

#include <libds/mm/memory_manager.h>
#include <libds/mm/memory_omanip.h>
#include <libds/constants.h>
#include <cstdlib>
#include <cstring>
#include <ostream>
#include <algorithm>
#include <iostream>

namespace ds::mm {

	template<typename BlockType>
	class CompactMemoryManager : public MemoryManager<BlockType> {
	public:
		CompactMemoryManager();
		CompactMemoryManager(size_t size);
		CompactMemoryManager(const CompactMemoryManager<BlockType>& other);
		~CompactMemoryManager() override;

		BlockType* allocateMemory() override;
		BlockType* allocateMemoryAt(size_t index);
		void releaseMemory(BlockType* pointer) override;
		void releaseMemoryAt(size_t index);
		void releaseMemory();

		size_t getCapacity() const;

		CompactMemoryManager<BlockType>& assign(const CompactMemoryManager<BlockType>& other);
		void changeCapacity(size_t newCapacity);
		void shrinkMemory();
		void clear();
		bool equals(const CompactMemoryManager<BlockType>& other) const;
		void* calculateAddress(const BlockType& data);
		size_t calculateIndex(const BlockType& data);
		BlockType& getBlockAt(size_t index);
		void swap(size_t index1, size_t index2);

		void print(std::ostream& os);

	private:
		size_t getAllocatedBlocksSize() const;
		size_t getAllocatedCapacitySize() const;

	private:
		BlockType* base_;
		BlockType* end_;
		BlockType* limit_;

		static const size_t INIT_SIZE = 4;
	};

	template<typename BlockType>
    CompactMemoryManager<BlockType>::CompactMemoryManager() :
		CompactMemoryManager(INIT_SIZE)
	{
	}

	template<typename BlockType>
    CompactMemoryManager<BlockType>::CompactMemoryManager(size_t size) :
		base_(static_cast<BlockType*>(std::calloc(size, sizeof(BlockType)))),
		end_(base_),
		limit_(base_ + size)
	{
	}

	template<typename BlockType>
    CompactMemoryManager<BlockType>::CompactMemoryManager(const CompactMemoryManager<BlockType>& other):
		CompactMemoryManager(other.getAllocatedBlockCount())
	{
		// TODO 02
		// po implementacii vymazte vyhodenie vynimky!
		throw std::runtime_error("Not implemented yet");
	}

	template<typename BlockType>
    CompactMemoryManager<BlockType>::~CompactMemoryManager()
	{
		// TODO 02
		// po implementacii vymazte vyhodenie vynimky!
		// throw std::runtime_error("Not implemented yet");
	}

	template<typename BlockType>
    BlockType* CompactMemoryManager<BlockType>::allocateMemory()
	{
		// TODO 02
		// po implementacii vymazte vyhodenie vynimky!
		throw std::runtime_error("Not implemented yet");
	}

	template<typename BlockType>
    BlockType* CompactMemoryManager<BlockType>::allocateMemoryAt(size_t index)
	{
		// TODO 02
		// po implementacii vymazte vyhodenie vynimky!
		throw std::runtime_error("Not implemented yet");
	}

	template<typename BlockType>
    void CompactMemoryManager<BlockType>::releaseMemory(BlockType* pointer)
	{
		if (pointer < base_ || pointer > limit_) {
			throw std::out_of_range("invalid index");
		}
		BlockType* ptr = pointer;
		while (ptr != end_) {
			ptr->~BlockType();
			++ptr;
		}
		end_ = pointer;
		this->allocatedBlockCount_ = end_ - base_;
		
	}

	template<typename BlockType>
    void CompactMemoryManager<BlockType>::releaseMemoryAt(size_t index)
	{
		throw std::runtime_error("Not implemented yet");
	}

	template<typename BlockType>
    void CompactMemoryManager<BlockType>::releaseMemory()
	{
		// TODO 02
		// po implementacii vymazte vyhodenie vynimky!
		throw std::runtime_error("Not implemented yet");
	}

	template<typename BlockType>
    size_t CompactMemoryManager<BlockType>::getCapacity() const
	{
		return (limit_ - base_);
	}

	template<typename BlockType>
    CompactMemoryManager<BlockType>& CompactMemoryManager<BlockType>::assign(const CompactMemoryManager<BlockType>& other) {
		// TODO 02
		// po implementacii vymazte vyhodenie vynimky!
		throw std::runtime_error("Not implemented yet");
	}

	template<typename BlockType>
    void CompactMemoryManager<BlockType>::shrinkMemory()
	{
		size_t newCapacity = end_ - base_;

		if (newCapacity < CompactMemoryManager<BlockType>::INIT_SIZE)
		{
			newCapacity = CompactMemoryManager<BlockType>::INIT_SIZE;
		}

		changeCapacity(newCapacity);
	}

	template<typename BlockType>
    void CompactMemoryManager<BlockType>::changeCapacity(size_t newCapacity)
	{
		if (newCapacity == this->getCapacity) {
			return;
		}
		if (newCapacity < this->getAllocatedBlockCount()) {
			this->releaseMemoryAt(base_ + newCapacity);
		}

		void* newBase = std::realloc(base_, newCapacity * BlockType);
		if (newBase == nullptr) {
			throw std::bad_alloc("failed to alloc");
		}
		base_ = newBase;
		end_ = newBase + this->getAllocatedBlockCount;
		limit_ = base_ + newCapacity;
		
	}

	template<typename BlockType>
    void CompactMemoryManager<BlockType>::clear()
	{
		// TODO 02
		// po implementacii vymazte vyhodenie vynimky!
		throw std::runtime_error("Not implemented yet");
	}

	template<typename BlockType>
    bool CompactMemoryManager<BlockType>::equals(const CompactMemoryManager<BlockType>& other) const
	{
		return (this == &other ||
			this->getAllocatedBlockCount() == other.getAllocatedBlockCount() &&
				std::memcmp(base_, other.base_, this->getAllocatedBlockCount() * sizeof(BlockType) == 0));
	}

	template<typename BlockType>
    void* CompactMemoryManager<BlockType>::calculateAddress(const BlockType& data)
	{
		//return this->calculateIndex(data) == -1 ? nullptr : &data; kvoli const problem a return void*
		BlockType* ptr = base_;
		while (ptr != limit_ || ptr != &data) {
			ptr++;
		}
		return ptr == end_ ? nullptr : ptr;

	}

	template<typename BlockType>
    size_t CompactMemoryManager<BlockType>::calculateIndex(const BlockType& data)
	{
		return &data >= base_ && &data < end_ ? &data - base_ : -1;
	}

	template<typename BlockType>
    BlockType& CompactMemoryManager<BlockType>::getBlockAt(size_t index)
	{
		return *(base_ + index);
	}

	template<typename BlockType>
    void CompactMemoryManager<BlockType>::swap(size_t index1, size_t index2)
	{
		std::swap(getBlockAt(index1), getBlockAt(index2));
	}

	template<typename BlockType>
    size_t CompactMemoryManager<BlockType>::getAllocatedBlocksSize() const
	{
		return (end_ - base_) * sizeof(BlockType);
	}

    template<typename BlockType>
    size_t CompactMemoryManager<BlockType>::getAllocatedCapacitySize() const
	{
		return (limit_ - base_)*sizeof(BlockType);
	}

	template<typename BlockType>
    void CompactMemoryManager<BlockType>::print(std::ostream& os)
	{
		os << "first = " << base_ << std::endl;
		os << "last = " << end_ << std::endl;
		os << "limit = " << limit_ << std::endl;
		os << "block size = " << sizeof(BlockType) << "B" << std::endl;

		BlockType* ptr = base_;
		while (ptr != limit_) {
			std::cout << ptr;
			os << PtrPrintBin<BlockType>(ptr);

			if (ptr == base_) {
				os << "<- first";
			}
			else if (ptr == end_) {
				os << "<- last";
			}
			os << std::endl;
			ptr++;
		}

		os << limit_ << "|<- limit" << std::endl;
	}

}