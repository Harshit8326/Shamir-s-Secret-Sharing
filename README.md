## 🔐 Secret Reconstruction using Polynomial Interpolation (C++)
This project reconstructs a secret using Lagrange Polynomial Interpolation, inspired by Shamir's Secret Sharing scheme.

## 📌 Features
Reconstructs a secret using any k out of n valid shares.

No external libraries used.

Manual base conversion (e.g., from base 3, 6, 7, etc.).

All math (like gcd) implemented manually without STL.

Selects the most frequent result from all nCk combinations for robustness.

## 📋 Input Format
The input is hardcoded in the C++ file in a JSON-like structure.

Each share contains:

base: the base in which the number is encoded (e.g., base 3, base 16).

value: the string representing the number in that base.

## Example:

json
Copy
Edit
{
  "keys": { "n": 10, "k": 7 },
  "1": { "base": "6", "value": "13444211440455345511" },
  "2": { "base": "15", "value": "aed7015a346d63" },
  "3": { "base": "15", "value": "6aeeb69631c227c" },
  ...
}
## ⚙️ How It Works
Input Parsing

JSON-like string parsed manually.

All numbers converted from their given base to decimal (long long).

Secret Recovery

All combinations of k shares are formed.

Lagrange Interpolation is applied to get the original secret.

The most common result among all combinations is chosen as the final answer.

Mathematical Routines

Modular Inverse and GCD are implemented manually.

## 🧪 Sample Output

The secret is: 1000000000000000029
## 🚀 How to Run
Open Answer.cpp in any C++17-supported compiler.

Compile:

bash
Copy
Edit
g++ -std=c++17 Answer.cpp -o secret
Run:

bash
Copy
Edit
./secret
🛠 Note
Works with values up to 10^18 using long long.

If you want to support larger numbers, consider implementing a BigInt class.

You can add more operations or formats easily.
