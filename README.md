# Elliptic Curve Diffie-Hellman Key Exchange (ECDHKE)

This repository contains a C implementation of the Elliptic Curve Diffie-Hellman Key Exchange (ECDHKE) protocol. The program demonstrates how two parties, Alice and Bob, can securely exchange cryptographic keys over an insecure channel using elliptic curve cryptography.

## Requirements

To compile and run this code, you will need:

- **GCC** (GNU Compiler Collection) to compile the C code.
- **GMP** (GNU Multiple Precision Arithmetic Library) for handling large integer arithmetic.
- **OpenSSL** for generating secure random numbers.

### Installing Dependencies

On Debian/Ubuntu-based systems, you can install the dependencies with the following commands:

```bash
sudo apt-get update
sudo apt-get install build-essential libgmp-dev libssl-dev
```

## Compilation

To compile the code, follow these steps:

1. Clone the repository or download the `elliptic_curve_dhke.c` file.
2. Navigate to the directory where the file is located.
3. Compile the code using GCC:

```bash
gcc -o elliptic_curve_dhke elliptic_curve_dhke.c -lgmp -lssl -lcrypto
```

This will generate an executable named `elliptic_curve_dhke`.

## Execution

Once compiled, you can run the program with the following command:

```bash
./elliptic_curve_dhke
```

### Example Usage

The program simulates the key exchange process between Alice and Bob using elliptic curve cryptography. Here’s how it works:

1. **Input Parameters**:
   - The program prompts the user to input the prime number \( p \), the coefficients \( a \) and \( b \) of the elliptic curve, and the generator point \( G \).

2. **Key Generation**:
   - Alice generates a private key \( k_A \) and computes her public key \( A = k_A \cdot G \).

3. **Key Exchange**:
   - Alice receives Bob's public key \( B \) and computes the shared secret \( K = k_A \cdot B \).

4. **Output**:
   - The program prints Alice's public key and the shared secret key.

#### Expected Output

Here is an example of the output:

```
Enter a prime number p (decimal, >= 4 bits): 23
Enter coefficient a for the elliptic curve: 1
Enter coefficient b for the elliptic curve: 1
Enter the generator point G coordinates (x, y, z):
x = 5
y = 7
z = 1
Random number: 6
Alice's public key A = k_A * G is: A(19, 20, 1)
Enter the public key B from Bob (coordinates x, y, z):
x = 17
y = 10
z = 1
Alice's shared key K = k_A * B is: K(13:10:1)
```

## Code Structure

- **`generate_secure_random`**: Generates a secure random number using OpenSSL's `RAND_bytes` function.
- **`alice_key_exchange`**: Implements the key exchange process for Alice, including private key generation, public key computation, and shared secret derivation.
- **`main`**: Handles user input and orchestrates the key exchange process.

## Contributions

If you would like to contribute to this project, feel free to fork the repository and submit a pull request with your improvements. Make sure to follow best coding practices and document any significant changes.

## Contact

If you have any questions or suggestions, please don't hesitate to reach out to me through my GitHub profile.

---

This project is a practical demonstration of elliptic curve cryptography and the Diffie-Hellman key exchange protocol. It is intended for educational purposes and provides a hands-on approach to understanding secure key exchange mechanisms.
