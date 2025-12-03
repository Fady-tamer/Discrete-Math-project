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

void solveExpression(int var_count, const string expression_name, const function<bool(bool, bool, bool)> expression)
{
    int num_rows = pow(2, var_count);
    cout << "=============================================\n";
    cout << "| Expression: " << expression_name << " is it TAUTOLOGY |" << "\n";
    cout << "=============================================\n";
    if (var_count == 2)
        cout << "| A | B |  B -> A  | " << expression_name << " |\n";
    else
        cout << "| A | B | C |  B -> C  | " << expression_name << " |\n";
    bool is_tautology = true;
    cout << "=============================================\n";
    for (int i = num_rows - 1; i >= 0; i--)
    {

        bool A = (var_count == 2) ? (i / 2) % 2 == 1 : (i / 4) % 2 == 1;
        bool B = (var_count == 2) ? i % 2 == 1 : (i / 2) % 2 == 1;
        bool C = (var_count == 2) ? unsigned{0} : i % 2 == 1;

        bool result = (var_count == 2) ? expression(A, B, C) : expression(A, B, C);
        if (result == false)
        {
            is_tautology = false;
        }
        cout << "| " << print_bool(A);
        cout << " | " << print_bool(B);
        if (var_count == 3)
        {
            cout << " | " << print_bool(C);
            cout << " |     " << print_bool(Implication(B, C));
        }
        else
            cout << " |     " << print_bool(Implication(B, A));
        cout << "    |       " << print_bool(result) << endl;
    }
    cout << "=============================================\n";
    if (is_tautology)
        cout << "| " << expression_name << " IS a TAUTOLOGY.\n";
    else
        cout << "| " << expression_name << " IS NOT a TAUTOLOGY.\n";
    cout << "=============================================\n\n";
}

void solve()
{
    solveExpression(
        3,
        "A -> (B -> C)",
        [](bool A, bool B, bool C)
        { return Implication(A, Implication(B, C)); });
    solveExpression(
        2,
        "A -> (B -> A)",
        [](bool A, bool B, unsigned)
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