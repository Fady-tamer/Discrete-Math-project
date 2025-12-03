#include <iostream>
#include <cmath>
#include <functional>

using namespace std;

#define ll long long
#define ld long double

void fady_tamer()
{
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}

bool Conjunction(bool p, bool q) { return p && q; }
bool Disjunction(bool p, bool q) { return p || q; }
bool Negation(bool p) { return !p; }
bool Implication(bool p, bool q) { return Negation(p) || q; }
// function to print 'T' for true and 'F' for false
string print_bool(bool val) { return val ? "T" : "F"; }

void solveExpression(int var_count, const string expression_name, const function<bool(bool, bool)> expression)
{
    int num_rows = var_count * var_count;
    cout << "=============================================\n";
    cout << "| Expression: " << expression_name << " is it TAUTOLOGY |" << "\n";
    cout << "=============================================\n";
    cout << "| A | B | (B -> A) | A -> (B -> A)\n";
    bool is_tautology = true;
    cout << "=============================================\n";
    for (int i = 0; i < num_rows; ++i)
    {
        bool A = (i / 2) % 2 == 1;
        bool B = i % 2 == 1;

        bool result = expression(A, B);
        if (result == false)
        {
            is_tautology = false;
        }
        cout << "| " << print_bool(A);
        if (var_count >= 2)
            cout << " | " << print_bool(B);
        cout << " |     " << print_bool(Implication(B, A));
        cout << "    |       " << print_bool(result) << endl;
    }
    cout << "=============================================\n";
    if (is_tautology)
        cout << "| " << expression_name << " IS a TAUTOLOGY.\n";
    cout << "=============================================";
}

void solve()
{
    solveExpression(
        2,
        "A -> (B -> A)",
        [](bool A, bool B)
        { return Implication(A, Implication(B, A)); });
}

signed main()
{
    fady_tamer();
    int tc = 1;
    // cin >> tc;
    for (int i = 1; i <= tc; i++)
    {
        solve();
    }
    return 0;
}