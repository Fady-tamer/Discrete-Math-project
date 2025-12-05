#include <iostream>
#include <cmath>
#include <functional>

using namespace std;

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
bool double_Implication(bool p, bool q) { return Implication(p, q) && Implication(q, p); }
string print_bool(bool val) { return val ? "T" : "F"; }
void get_truth_values(int i, int var_count, bool &P, bool &Q, bool &R)
{
    if (var_count == 3)
    {
        P = (i / 4) % 2 == 1;
        Q = (i / 2) % 2 == 1;
        R = i % 2 == 1;
    }
    else if (var_count == 2)
    {
        P = (i / 2) % 2 == 1;
        Q = i % 2 == 1;
        R = false;
    }
    else
    {
        P = i % 2 == 1;
        Q = false;
        R = false;
    }
}

void compareExpressions(int var_count, const string LHS_name, const string RHS_name, const function<bool(bool, bool, bool)> LHS_func, const function<bool(bool, bool, bool)> RHS_func)
{
    int num_rows = pow(2, var_count);

    cout << "==================================================================================\n";
    cout << "| Checking Equivalence: " << LHS_name << " <=> " << RHS_name << "\n";
    cout << "==================================================================================\n";
    cout << "| " << "P" << " | " << "Q";
    if (var_count == 3)
        cout << " | " << "R";
    cout << " | " << "LHS" << " | " << "RHS" << " | " << "Match" << " |\n";
    cout << "==================================================================================\n";

    bool is_equivalence = true;
    for (int i = 0; i < num_rows; i++)
    {
        bool P, Q, R;
        get_truth_values(i, var_count, P, Q, R);
        bool LHS_result = LHS_func(P, Q, R);
        bool RHS_result = RHS_func(P, Q, R);
        bool match = (LHS_result == RHS_result);
        if (!match)
        {
            is_equivalence = false;
        }
        cout << "| " << print_bool(P);
        cout << " | " << print_bool(Q);
        if (var_count == 3)
            cout << " | " << print_bool(R);
        cout << " |  " << print_bool(LHS_result);
        cout << "  |  " << print_bool(RHS_result);
        cout << "  |   " << (match ? "T" : "F") << "   |\n";
    }

    cout << "==================================================================================\n";
    if (is_equivalence)
        cout << "| " << LHS_name << " and " << RHS_name << " ARE EQUIVALENT.|\n";
    else
        cout << "| " << LHS_name << " and " << RHS_name << " ARE NOT EQUIVALENT.|\n";
    cout << "==================================================================================\n\n";
}

void solve()
{
    auto LHS_logic = [](bool P, bool Q, bool R)
    {
        bool term1 = Conjunction(P, Negation(R));
        bool term2_inner1 = Disjunction(P, Negation(Q));
        bool term2_inner2 = Disjunction(Q, Negation(P));
        bool term2 = Conjunction(term2_inner1, term2_inner2);
        return Disjunction(term1, term2);
    };

    auto RHS_logic = [](bool P, bool Q, bool R)
    {
        bool term1 = Conjunction(P, Negation(R));
        bool term2 = double_Implication(Q, P);
        return Disjunction(term1, term2);
    };
    compareExpressions(
        3,
        "(p ^ ~r) v (p v ~q) ^ (q v ~p)",
        "(p ^ ~r) v (q <-> p)",
        LHS_logic, RHS_logic);
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