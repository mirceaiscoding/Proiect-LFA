#include <fstream>
#include <vector>
using namespace std;
ifstream fin("nfa.in");
ofstream fout("nfa.out");

class Muchie
{

private:
    int targetNode;    /// Nod tinta
    char charRequired; /// Caracterul cu care se ajunge in nodul tinta

public:
    Muchie(int targetNode, char charRequired)
    {
        this->targetNode = targetNode;
        this->charRequired = charRequired;
    }

    int getTargetNode()
    {
        return targetNode;
    }

    char getCharRequired()
    {
        return charRequired;
    }
};

/// Presupunem ca numarul de noduri este maxim 1000
/// n = numar de noduri
/// m = numar de muchii
/// startNode = nodul de intrare
/// endNodes = vector cu nodurile de iesire
/// t = numarul de cuvinte testate
/// sol = vector folosit pentru a recrea solutia
int n, m, startNode, numberOfEndNodes, t;
bool isAccepted;
vector<int> endNodes;
vector<Muchie> a[1001];
vector<int> sol;

bool isEndNode(int node)
{
    for (int i = 0; i < endNodes.size(); i++)
    {
        if (endNodes[i] == node)
        {
            return true;
        }
    }
    return false;
}

void dfs(int nod, string remainingWord)
{

    if (isAccepted == true)
    {
        /// Avem deja solutie deci ne oprim
        return;
    }

    if (remainingWord == "" && isEndNode(nod))
    {
        isAccepted = true;
        /// Acest nod face parte din solutie
        sol.push_back(nod);
        return;
    }

    for (int i = 0; i < a[nod].size(); i++)
    {
        Muchie muchie = a[nod][i];
        int target = muchie.getTargetNode();
        char ch = muchie.getCharRequired();
        if (ch == remainingWord[0])
        {
            /// dfs(targetNode, remainingWord[1:])
            dfs(target, remainingWord.substr(1, remainingWord.size() - 1));
        }
    }

    if (isAccepted == true)
    {
        /// Acest nod face parte din solutie deoarece nu aveam
        /// solutie cand am intrat in el, dar acum avem.
        sol.push_back(nod);
    }
}

int main()
{

    fin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int x, y;
        char ch;
        fin >> x >> y >> ch;
        Muchie muchieCrt(y, ch);
        a[x].push_back(muchieCrt);
    }

    fin >> startNode;

    fin >> numberOfEndNodes;
    for (int i = 0; i < numberOfEndNodes; i++)
    {
        int endNode;
        fin >> endNode;
        endNodes.push_back(endNode);
    }

    fin >> t;

    while (t)
    {
        string word; /// Cuvantul care trebuie testat
        fin >> word;

        isAccepted = false;
        sol.clear();
        dfs(startNode, word);

        if (isAccepted)
        {
            fout << "DA\n";
            /// Afisam solutia
            fout << "Traseu: ";
            for (int i = sol.size() - 1; i >= 0; i--)
            {
                fout << sol[i] << " ";
            }
            fout << "\n";
        }
        else
        {
            fout << "NU\n";
        }
        t--;
    }
}
