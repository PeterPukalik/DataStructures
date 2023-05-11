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
    template<class List>
    class TableAnalyzer : public ComplexityAnalyzer<List>
    {
    protected:
        explicit TableAnalyzer(const std::string& name);

    protected:
        void beforeOperation(List& structure) override;
        //size_t getRandomIndex() const;
        int getRandomData() const;

    private:
        void insertNElements(List& list, size_t n);

    private:
        std::default_random_engine rngData_;
        std::default_random_engine rngIndex_;
        size_t index_;
        int data_;
    };


    /**
     * @brief Analyzes complexity of the insert operation.
     */
    template<class List>
    class TableInsertAnalyzer : public TableAnalyzer<List>
    {
    public:
        explicit ListInsertAnalyzer(const std::string& name);

    protected:
        void executeOperation(List& structure) override;
    };
}