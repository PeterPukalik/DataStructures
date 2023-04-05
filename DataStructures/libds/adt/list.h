#pragma once

#include <libds/adt/abstract_data_type.h>
#include <libds/amt/implicit_sequence.h>
#include <libds/amt/explicit_sequence.h>

namespace ds::adt {

    template <typename T>
    class List :
        virtual public ADT
    {
    public:
        virtual size_t calculateIndex(T element) = 0;

        virtual bool contains(T element) = 0;

        virtual T accessFirst() = 0;
        virtual T accessLast() = 0;
        virtual T access(size_t index) = 0;

        virtual void insertFirst(T element) = 0;
        virtual void insertLast(T element) = 0;
        virtual void insert(T element, size_t index) = 0;

        virtual void set(size_t index, T element) = 0;

        virtual void removeFirst() = 0;
        virtual void removeLast() = 0;
        virtual void remove(size_t index) = 0;
    };

    //----------

    template <typename T, typename SequenceType>
    class GeneralList :
        virtual public List<T>,
        public ADS<T>
    {
    public:
        using IteratorType = typename SequenceType::IteratorType;

    public:
        GeneralList();
        GeneralList(const GeneralList& other);

        size_t calculateIndex(T element) override;

        bool contains(T element) override;

        T accessFirst() override;
        T accessLast() override;
        T access(size_t index) override;

        void insertFirst(T element) override;
        void insertLast(T element) override;
        void insert(T element, size_t index) override;

        void set(size_t index, T element) override;

        void removeFirst() override;
        void removeLast() override;
        void remove(size_t index) override;

        IteratorType begin();
        IteratorType end();

    protected:
        SequenceType* getSequence() const;
    };

    //----------

    template <typename T>
    class ImplicitList :
        public GeneralList<T, amt::IS<T>>
    {
    };

    //----------

    template <typename T>
    class ImplicitCyclicList :
        public GeneralList<T, amt::CIS<T>>
    {
    };

    //----------

    template <typename T>
    class SinglyLinkedList :
        public GeneralList<T, amt::SinglyLS<T>>
    {
    };

    //----------

    template <typename T>
    class SinglyCyclicLinkedList :
        public GeneralList<T, amt::SinglyCLS<T>>
    {
    };

    //----------

    template <typename T>
    class DoublyLinkedList :
        public GeneralList<T, amt::DoublyLS<T>>
    {
    };

    //----------

    template <typename T>
    class DoublyCyclicLinkedList :
        public GeneralList<T, amt::DoublyCLS<T>>
    {
    };

    //----------

    template<typename T, typename SequenceType>
    GeneralList<T, SequenceType>::GeneralList() :
        ADS<T>(new SequenceType())
    {
    }

    template<typename T, typename SequenceType>
    GeneralList<T, SequenceType>::GeneralList(const GeneralList& other) :
        ADS<T>(new SequenceType(), other)
    {
    }

    template<typename T, typename SequenceType>
    size_t GeneralList<T, SequenceType>::calculateIndex(T element)
    {
        size_t result = 0;

        if (getSequence()->findBlockWithProperty([&result, &element](*BlockType block) // [&] posleem si tam vsetko
            {
                if (block->data_ == element) {
                    return true;
                }
                else {
                    result++;
                    return false;
                }
            }) == nullptr) {
            return INVALID_INDEX;
        }

        return result;
    }

    template<typename T, typename SequenceType>
    bool GeneralList<T, SequenceType>::contains(T element)
    {
        return this->calculateIndex(element) != INVALID_INDEX;
    }

    template<typename T, typename SequenceType>
    T GeneralList<T, SequenceType>::accessFirst()
    {
        auto block = getSequence()->accessFirst();
        if (block == nullptr) {
            throw std::out_of_range("No first element in list!");
        }
        return block->data_;
        
    }

    template<typename T, typename SequenceType>
    T GeneralList<T, SequenceType>::accessLast()
    {
        auto block = getSequence()->accessLast();
        if (block == nullptr) {
            throw std::out_of_range("No first element in list!");
        }
        return block->data_;
    }

    template<typename T, typename SequenceType>
    T GeneralList<T, SequenceType>::access(size_t index)
    {
        auto block = getSequence()->acces(index);
        if (block == nullptr) {
            throw std::out_of_range("No elemenet with this index inlist!");
        }
        return block->data_;

    }

    template<typename T, typename SequenceType>
    void GeneralList<T, SequenceType>::insertFirst(T element)
    {
       getSequence()->insertFirst()->data_ = element;
    }

    template<typename T, typename SequenceType>
    void GeneralList<T, SequenceType>::insertLast(T element)
    {
        getSequence()->insertLast()->data_ = element;
    }

    template<typename T, typename SequenceType>
    void GeneralList<T, SequenceType>::insert(T element, size_t index)
    {
        if (index < 0 || index > size()) {
            throw std::out_of_range("invalid index");
        }
        getSequence()->insert(index)->data_ = element;
    }

    template<typename T, typename SequenceType>
    void GeneralList<T, SequenceType>::set(size_t index, T element)
    {
        auto block = ;
        if (block == nullptr) {
            throw std::out_of_range("No elemenet with this index inlist!");
        }
        getSequence()->access(index)->data_ = element;
    }

    template<typename T, typename SequenceType>
    void GeneralList<T, SequenceType>::removeFirst()
    {
        if (isEmpty()) {
            throw std::out_of_range("list is empty");
        }
        //auto result = getSequence()->accessFirst()->data_;
        getSequence()->removeFirst();

    }

    template<typename T, typename SequenceType>
    void GeneralList<T, SequenceType>::removeLast()
    {
        if (isEmpty()) {
            throw std::out_of_range("list is empty");
        }
        //auto result = getSequence()->accessLast()->data_;
        getSequence()->removeLast();

    }

    template<typename T, typename SequenceType>
    void GeneralList<T, SequenceType>::remove(size_t index)
    {
        if (isEmpty()) {
            throw std::out_of_range("list is empty");
        }
        //auto result = getSequence()->access(ondex)->data_;
        getSequence()->remove(index);
    }

    template <typename T, typename SequenceType>
    auto GeneralList<T, SequenceType>::begin() -> IteratorType
    {
        return getSequence()->begin();
    }

    template <typename T, typename SequenceType>
    auto GeneralList<T, SequenceType>::end() -> IteratorType
    {
        return getSequence()->end();
    }

    template<typename T, typename SequenceType>
    SequenceType* GeneralList<T, SequenceType>::getSequence() const
    {
        return dynamic_cast<SequenceType*>(this->memoryStructure_);
    }
}