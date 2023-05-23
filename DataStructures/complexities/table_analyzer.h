#pragma once

#include <complexities/complexity_analyzer.h>
#include <iterator>
#include <list>
#include <random>
#include <vector>
#include <libds/adt/table.h>

namespace ds::utils
{
    /**
 * @brief Common base for list analyzers.
 */
    template<class Table>
    class TableAnalyzer : public ComplexityAnalyzer<Table>
    {
    protected:
        explicit TableAnalyzer(const std::string& name);

    protected:
        void beforeOperation(Table& structure) override;
        //size_t getRandomIndex() const;
        int getRandomData() const;

    private:
        void insertNElements(Table& table, size_t n);

    private:
        std::default_random_engine rngData_;
        size_t index_;
        int data_;
    };


    /**
     * @brief Analyzes complexity of the insert operation.
     */
    template<class Table>
    class TableInsertAnalyzer : public TableAnalyzer<Table>
    {
    public:
        explicit TableInsertAnalyzer(const std::string& name);

    protected:
        void executeOperation(Table& structure) override;
    };

    /**
 * @brief Analyzes complexity of the insert operation.
 */
    template<class Table>
    class TableRemoveAnalyzer : public TableAnalyzer<Table>
    {
    public:
        explicit TableRemoveAnalyzer(const std::string& name);

    protected:
        void executeOperation(Table& structure) override;
    };


    class TablesAnalyzer : public CompositeAnalyzer
    {
    public:
        TablesAnalyzer() :
            CompositeAnalyzer("Table")
        {
            this->addAnalyzer(std::make_unique<TableInsertAnalyzer<ds::adt::Treap<int,int>>>("Treap-insert"));
            this->addAnalyzer(std::make_unique<TableRemoveAnalyzer<ds::adt::Treap<int, int>>>("Treap-remove"));

        }
    };
    template<class Table>
    inline TableAnalyzer<Table>::TableAnalyzer(const std::string& name)
    {
    }
}