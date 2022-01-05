# Very Cursed Implementation of SHA3

This is a cursed implementation of SHA3 utilizing C++ templates to provide access to Keccak-f state as a N dimensional array and at the same time as a 1 dimensional array. This makes the Keccak-f code very clear and straightforward at the cost of obfuscating everything else. However, thanks to C++ compiler optimization our implementation is only slightly slower than the pure C one in openssl.

## Build

```sh=
mkdir build
cd build
cmake ..
make
```

## Run

```sh=
echo "DATA" | ./sha3 sha3_512|sha3_384|sha3_256|sha3_224
```
