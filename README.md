# Secret Reconstruction using Polynomial Interpolation (C++)

This project implements a secret reconstruction algorithm inspired by **Shamir's Secret Sharing**. The secret is recovered from a set of shares using **Lagrange Interpolation**.

## 🔧 Features

- Reads JSON input directly from a hardcoded string in the C++ file.
- Computes values from operations like:
  - `sum`
  - `multiply`
  - `gcd`
- Handles incorrect shares by checking all combinations of shares (`nCk`) and selecting the most common result.
- Uses manual parsing and built-in data types (`long long`).

## 📋 Input Format

The JSON contains:
- `n`: Total number of shares.
- `k`: Threshold needed to reconstruct the secret.
- `shares`: A map of share ID to operation with values.

Example format:
json
{
  "n": 5,
  "k": 3,
  "shares": {
    "1": { "op": "sum", "a": 1000000000000000000, "b": 29 },
    "2": { "op": "multiply", "a": 7, "b": 900000000000000003 },
    "3": { "op": "gcd", "a": 391, "b": 17 },
    ...
  }
}
JSON is parsed manually from a string inside the C++ code — no external libraries are used.
## 🚀 How It Works
Each share is computed using the operation and values.

All k-combinations of shares are formed.

Lagrange Interpolation is applied to reconstruct the secret.

The most frequently appearing secret is selected as the valid one.

## 🛠 How to Run
Open the C++ file in your editor.

## Compile and run:

g++ secret_reconstruction.cpp -o secret
./secret

## Output:
The secret is: 1000000000000000029
## 📌 Note
The code uses long long. If your values go beyond 10^18, consider implementing a custom BigInt class.

You can expand the parser and computation logic to support more operations like lcm, subtract, etc.

## 📁 File
Answer.cpp: Main C++ file containing all logic.









Ask ChatGPT

