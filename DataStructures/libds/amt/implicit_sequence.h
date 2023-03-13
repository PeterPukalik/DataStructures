#pragma once

#include <libds/amt/abstract_memory_type.h>
#include <libds/amt/sequence.h>

namespace ds::amt {

	template<typename DataType>
	class ImplicitSequence :
		public Sequence<MemoryBlock<DataType>>,
		public ImplicitAMS<DataType>
	{
	public:
		using BlockType = MemoryBlock<DataType>;

		ImplicitSequence();
		ImplicitSequence(size_t capacity, bool initBlocks);
		ImplicitSequence(const ImplicitSequence<DataType>& other);
		~ImplicitSequence() override;

		size_t calculateIndex(MemoryBlock<DataType>& block) override;

		BlockType* accessFirst() const override;
		BlockType* accessLast() const override;
		BlockType* access(size_t index) const override;
		BlockType* accessNext(const BlockType& block) const override;
		BlockType* accessPrevious(const BlockType& block) const override;

		BlockType& insertFirst() override;
		BlockType& insertLast() override;
		BlockType& insert(size_t index) override;
		BlockType& insertAfter(const BlockType& block) override;
		BlockType& insertBefore(const BlockType& block) override;

		void removeFirst() override;
		void removeLast() override;
		void remove(size_t index) override;
		void removeNext(const MemoryBlock<DataType>& block) override;
		void removePrevious(const MemoryBlock<DataType>& block) override;

		void reserveCapacity(size_t capacity);

		virtual size_t indexOfNext(size_t currentIndex) const;
		virtual size_t indexOfPrevious(size_t currentIndex) const;

	public:
		class ImplicitSequenceIterator {
		public:
			ImplicitSequenceIterator(ImplicitSequence<DataType>* sequence, size_t index);
			ImplicitSequenceIterator(const ImplicitSequenceIterator& other);
			ImplicitSequenceIterator& operator++();
			ImplicitSequenceIterator operator++(int);
			bool operator==(const ImplicitSequenceIterator& other) const;
			bool operator!=(const ImplicitSequenceIterator& other) const;
			DataType& operator*();

		private:
			ImplicitSequence<DataType>* sequence_;
			size_t position_;
		};

		ImplicitSequenceIterator begin();
		ImplicitSequenceIterator end();

		using IteratorType = ImplicitSequenceIterator;
	};

	template<typename DataType>
	using IS = ImplicitSequence<DataType>;

	//----------

	template<typename DataType>
	class CyclicImplicitSequence : public IS<DataType>
	{
	public:
		CyclicImplicitSequence();
		CyclicImplicitSequence(size_t initSize, bool initBlocks);

		size_t indexOfNext(size_t currentIndex) const override;
		size_t indexOfPrevious(size_t currentIndex) const override;
	};

	template<typename DataType>
	using CIS = CyclicImplicitSequence<DataType>;

	//----------

	template<typename DataType>
    ImplicitSequence<DataType>::ImplicitSequence()
	{
	}

	template<typename DataType>
    ImplicitSequence<DataType>::ImplicitSequence(size_t initialSize, bool initBlocks):
		ImplicitAMS<DataType>(initialSize, initBlocks)
	{
	}

	template<typename DataType>
    ImplicitSequence<DataType>::ImplicitSequence(const ImplicitSequence<DataType>& other):
		ImplicitAMS<DataType>::ImplicitAbstractMemoryStructure(other)
	{
	}

	template<typename DataType>
    ImplicitSequence<DataType>::~ImplicitSequence()
	{
	}

	template<typename DataType>
    size_t ImplicitSequence<DataType>::calculateIndex(BlockType& block)
	{
		// TODO 03
		// po implementacii vymazte vyhodenie vynimky!
		return this->getMemoryManager()->calculateIndex(block);
	}

	template<typename DataType>
    MemoryBlock<DataType>* ImplicitSequence<DataType>::accessFirst() const
	{
		// TODO 03
		// po implementacii vymazte vyhodenie vynimky!
		return size() > 0 ? &this->getMemoryManager()->getBlockAt(0) : nullptr;
	}

	template<typename DataType>
    MemoryBlock<DataType>* ImplicitSequence<DataType>::accessLast() const
	{
		return size() > 0 ? &this->getMemoryManager()->getBlockAt(size() - 1) : nullptr;
	}

	template<typename DataType>
    MemoryBlock<DataType>* ImplicitSequence<DataType>::access(size_t index) const
	{
		return index < size() ? &this->getMemoryManager()->getBlockAt(index) : nullptr;
	}

	template<typename DataType>
    MemoryBlock<DataType>* ImplicitSequence<DataType>::accessNext(const MemoryBlock<DataType>& block) const
	{
		// TODO 03
		// po implementacii vymazte vyhodenie vynimky!
		auto indexCurrent = indexOfNext(this->getMemoryManager()->calculateIndex(block));
		return indexCurrent != INVALID_INDEX ? &this->getMemoryManager()->getBlockAt(indexCurrent) : nullptr;
		//return indexCurrent < size() ? &this->getMemoryManager()->getBlockAt(indexCurrent) : nullptr;
		
	}

	template<typename DataType>
    MemoryBlock<DataType>* ImplicitSequence<DataType>::accessPrevious(const MemoryBlock<DataType>& block) const
	{
		auto indexCurrent = indexOfPrevious(this->getMemoryManager()->calculateIndex(block));
		return indexCurrent != INVALID_INDEX ? &this->getMemoryManager()->getBlockAt(indexCurrent) : nullptr;
		//return indexCurrent >= 0 ? &this->getMemoryManager()->getBlockAt(indexCurrent) : nullptr;
		
	}

	template<typename DataType>
    MemoryBlock<DataType>& ImplicitSequence<DataType>::insertFirst()
	{
		// TODO 03
		// po implementacii vymazte vyhodenie vynimky!
		return *this->getMemoryManager()->allocateMemoryAt(0);
	}

	template<typename DataType>
    MemoryBlock<DataType>& ImplicitSequence<DataType>::insertLast()
	{
		// TODO 03
		// po implementacii vymazte vyhodenie vynimky!
		return *this->getMemoryManager()->allocateMemory();
	}

	template<typename DataType>
    MemoryBlock<DataType>& ImplicitSequence<DataType>::insert(size_t index)
	{
		// TODO 03
		// po implementacii vymazte vyhodenie vynimky!
		return *this->getMemoryManager()->allocateMemoryAt(index);
	}

	template<typename DataType>
    MemoryBlock<DataType>& ImplicitSequence<DataType>::insertAfter(const MemoryBlock<DataType>& block)
	{
		// TODO 03
		// po implementacii vymazte vyhodenie vynimky!
		return *this->getMemoryManager()->allocateMemoryAt(this->getMemoryManager()->calculateIndex(block) + 1);
	}

	template<typename DataType>
    MemoryBlock<DataType>& ImplicitSequence<DataType>::insertBefore(const MemoryBlock<DataType>& block)
	{
		// TODO 03
		// po implementacii vymazte vyhodenie vynimky!
		return *this->getMemoryManager()->allocateMemoryAt(this->getMemoryManager()->calculateIndex(block));


	}

	template<typename DataType>
    void ImplicitSequence<DataType>::removeFirst()
	{
		// TODO 03
		// po implementacii vymazte vyhodenie vynimky!
		this->getMemoryManager()->releaseMemoryAt(0);
	}

	template<typename DataType>
    void ImplicitSequence<DataType>::removeLast()
	{
		// TODO 03
		// po implementacii vymazte vyhodenie vynimky!
		this->getMemoryManager()->releaseMemory();
	}

	template<typename DataType>
    void ImplicitSequence<DataType>::remove(size_t index)
	{
		// TODO 03
		// po implementacii vymazte vyhodenie vynimky!
		this->getMemoryManager()->releaseMemoryAt(index);
	}

	template<typename DataType>
    void ImplicitSequence<DataType>::removeNext(const MemoryBlock<DataType>& block)
	{
		// TODO 03
		// po implementacii vymazte vyhodenie vynimky!
		this->getMemoryManager()->releaseMemoryAt(indexOfNext(this->getMemoryManager()->calculateIndex(block)));
	}

	template<typename DataType>
    void ImplicitSequence<DataType>::removePrevious(const MemoryBlock<DataType>& block)
	{
		// TODO 03
		// po implementacii vymazte vyhodenie vynimky!
		this->getMemoryManager()->releaseMemoryAt(indexOfPrevious(this->getMemoryManager()->calculateIndex(block)));
	}

	template<typename DataType>
    void ImplicitSequence<DataType>::reserveCapacity(size_t capacity)
	{
		// TODO 03
		// po implementacii vymazte vyhodenie vynimky!
		this->getMemoryManager()->changeCapacity(capacity);
	}

	template<typename DataType>
    size_t ImplicitSequence<DataType>::indexOfNext(size_t currentIndex) const
	{
		// TODO 03
		// po implementacii vymazte vyhodenie vynimky!

		//return currentIndex >= size() - 1 ? INVALID_INDEX : currentIndex + 1;
		return currentIndex >= size() - 1 ? INVALID_INDEX : currentIndex + 1;
	}

	template<typename DataType>
    size_t ImplicitSequence<DataType>::indexOfPrevious(size_t currentIndex) const
	{
		// TODO 03
		// po implementacii vymazte vyhodenie vynimky!
		//if (currentIndex <= 0) {
			//return -1;
		//}
		//else {
			//return currentIndex--;
		//}
		//return currentIndex == 0 ? INVALID_INDEX : currentIndex - 1;
		return currentIndex == 0 ? INVALID_INDEX : currentIndex - 1;
	}

    template <typename DataType>
    ImplicitSequence<DataType>::ImplicitSequenceIterator::ImplicitSequenceIterator
        (ImplicitSequence<DataType>* sequence, size_t index) :
		    sequence_(sequence),
            position_(index)
    {
    }

    template <typename DataType>
    ImplicitSequence<DataType>::ImplicitSequenceIterator::ImplicitSequenceIterator
        (const ImplicitSequenceIterator& other) :
		    sequence_(other.sequence_),
            position_(other.position_)
    {
    }

    template <typename DataType>
    auto ImplicitSequence<DataType>::ImplicitSequenceIterator::operator++() -> ImplicitSequenceIterator&
    {
		// TODO 03
		// po implementacii vymazte vyhodenie vynimky!
		++position_;
		return *this;
    }

    template <typename DataType>
    auto ImplicitSequence<DataType>::ImplicitSequenceIterator::operator++(int) -> ImplicitSequenceIterator
    {
		ImplicitSequenceIterator tmp(*this);
	    this->operator++();
	    return tmp;
    }

    template <typename DataType>
    bool ImplicitSequence<DataType>::ImplicitSequenceIterator::operator==(const ImplicitSequenceIterator& other) const
    {
		return position_ == other.position_;//&& sequence_ == other.sequence_; //sekvencie nemusim porovnavat
    }

    template <typename DataType>
    bool ImplicitSequence<DataType>::ImplicitSequenceIterator::operator!=(const ImplicitSequenceIterator& other) const
    {
		return !(*this == other);
    }

    template <typename DataType>
    DataType& ImplicitSequence<DataType>::ImplicitSequenceIterator::operator*()
    {
		// TODO 03
		// po implementacii vymazte vyhodenie vynimky!
		return sequence_->access(position_)->data_;
    }

    template <typename DataType>
    auto ImplicitSequence<DataType>::begin() -> ImplicitSequenceIterator
    {
		return ImplicitSequenceIterator(this, 0);
    }

    template <typename DataType>
    auto ImplicitSequence<DataType>::end() -> ImplicitSequenceIterator
    {
		return ImplicitSequenceIterator(this, ImplicitAbstractMemoryStructure<DataType>::size());
    }

    template<typename DataType>
    CyclicImplicitSequence<DataType>::CyclicImplicitSequence():
		IS<DataType>()
	{
	}

	template<typename DataType>
    CyclicImplicitSequence<DataType>::CyclicImplicitSequence(size_t initCapacity, bool initBlocks):
		IS<DataType>(initCapacity, initBlocks)
	{
	}

	template<typename DataType>
    size_t CyclicImplicitSequence<DataType>::indexOfNext(size_t currentIndex) const
	{
		// TODO 03
		const size_t size = this->size();
		return size != 0 ? currentIndex >= size - 1 ? 0 : currentIndex + 1 : INVALID_INDEX;
	}

	template<typename DataType>
    size_t CyclicImplicitSequence<DataType>::indexOfPrevious(size_t currentIndex) const
	{
		const size_t size = this->size();
		return size != 0 ? currentIndex <= 0 ? size - 1 : currentIndex - 1 : INVALID_INDEX;
	}

}