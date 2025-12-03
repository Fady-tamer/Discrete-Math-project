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
void compareExpressions(int var_count, const string LHS, const string RHS, const function<bool(bool, bool, bool)> expression, const function<bool(bool, bool, bool)> other_expression)
{
    int num_rows = pow(2, var_count);
    cout << "=============================================\n";
    cout << "| Expression: " << LHS << " (L.H.S) |" << "\n";
    cout << "=============================================\n";
    cout << "| A | B | " << LHS << " |\n";
    cout << "=============================================\n";

    bool is_equivalence = true;
    for (int i = num_rows - 1; i >= 0; i--)
    {

        bool A = (var_count == 2) ? (i / 2) % 2 == 1 : (i / 4) % 2 == 1;
        bool B = (var_count == 2) ? i % 2 == 1 : (i / 2) % 2 == 1;
        bool C = (var_count == 2) ? unsigned{0} : i % 2 == 1;

        bool LHS = (var_count == 2) ? expression(A, B, C) : expression(A, B, C);
        bool RHS = (var_count == 2) ? other_expression(A, B, C) : other_expression(A, B, C);
        if (LHS != RHS)
        {
            is_equivalence = false;
        }
        cout << "| " << print_bool(A);
        cout << " | " << print_bool(B);
        cout << " |   " << print_bool(LHS) << endl;
    }

    cout << "=============================================\n";
    cout << "| Expression: " << RHS << " (R.H.S) |" << "\n";
    cout << "=============================================\n";
    cout << "| A | B | " << RHS << " |\n";
    cout << "=============================================\n";

    for (int i = num_rows - 1; i >= 0; i--)
    {

        bool A = (var_count == 2) ? (i / 2) % 2 == 1 : (i / 4) % 2 == 1;
        bool B = (var_count == 2) ? i % 2 == 1 : (i / 2) % 2 == 1;
        bool C = (var_count == 2) ? unsigned{0} : i % 2 == 1;

        bool LHS = (var_count == 2) ? expression(A, B, C) : expression(A, B, C);
        bool RHS = (var_count == 2) ? other_expression(A, B, C) : other_expression(A, B, C);
        if (LHS != RHS)
        {
            is_equivalence = false;
        }
        cout << "| " << print_bool(A);
        cout << " | " << print_bool(B);
        cout << " |   " << print_bool(RHS) << endl;
    }

    cout << "=============================================\n";
    if (is_equivalence)
        cout << "| " << LHS << " and " << RHS << " is equivalence.\n";
    else
        cout << "| " << LHS << " and " << RHS << " is't equivalence.\n";
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
    compareExpressions(
        2,
        "A ^ B",
        "B ^ A",
        [](bool A, bool B, unsigned)
        { return Conjunction(A, B); },
        [](bool A, bool B, unsigned)
        { return Conjunction(B, A); });
    compareExpressions(
        2,
        "A ^ B",
        "B -> A",
        [](bool A, bool B, unsigned)
        { return Conjunction(A, B); },
        [](bool A, bool B, unsigned)
        { return Implication(B, A); });
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