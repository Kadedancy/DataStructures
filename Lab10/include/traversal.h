#pragma once
#include <map>

namespace misc 
{
    class Traversal 
    {
    private:
        std::map<X,X> mTraversalHistory;

    public:
        void addToTraversalHistory(int node);

        const std::vector<int>& getTraversalHistory() const;
    };
}