
#pragma once
#include <vector>
#include <queue>
#include <unordered_set>
#include "../includes/Conflict.h"

// A* Planner
class A_star
{
public:
	A_star(Environment *env);

	bool plan(State *startState, std::vector<State*> &solution, 
        std::vector<Constraint*> relevantConstraints, 
        std::vector<std::vector<State*>>& parent);

	struct Node
	{
    	Node(State *state, double hScore, 
    		double gScore = std::numeric_limits<double>::infinity())
        	: state(state), gScore(gScore), hScore(hScore), parent{nullptr} {}

    	friend std::ostream& operator<<(std::ostream& os, const Node& node)
    	{
    	  os << "state: " << node.state << " fScore: " << (node.gScore + node.hScore);
    	  return os;
    	}

    	// gScore = is the cost of the path from the start node
    	// hScore = heuristic cost function (Equclidean dist from node to goal)
    	State *state;
    	Node *parent;
    	double gScore;
    	double hScore;
        double segCost{0};
	};

    int SegHeuristic(Node *n, std::vector<std::vector<State*>>& otherSols);

    bool is_disjoint(const std::vector<State*> v1, 
        const std::vector<State*> v2) const;

	// To compare two Nodes -- f(n) = g(n) + h(n)
	// calculate the best next-node from open heap
	class myComparator
	{
	public:
    	int operator() (const Node *n1, const Node *n2)
    	{
    		double fScore1 = n1->gScore + n1->hScore;
    		double fScore2 = n2->gScore + n2->hScore;
        	return fScore1 > fScore2;
    	}
	};

	Environment* getEnv() {return m_env;};
private:
	Environment *m_env;
};