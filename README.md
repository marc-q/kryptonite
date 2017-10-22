# Kryptonite
A way people could have secure passwords.

## How to compile Kryptonite?

1. Make sure that the package `libssl-dev` is installed.
2. Run `$ make` inside the repository.

## How to generate Kryptons?

**IMPORTANT** Make sure you create and use a custom encoding function in order to create secure password's.

1. Run Kryptonite with the secret you want to remeber as the first argument.

**Example:**

```
$ ./kryptonite "Ta1K_uO7+github.com" 
WARNING: YOU NEED TO IMPLEMENT YOUR OWN CUSTOM ENCODING FUNCTION!

PW:		Ta1K_uO7+github.com
Krypton:	hvv2zslMExD4s/wv0Ukl/iWMnI/lnqxcKHaOQ0MyKO8/
```

If `Ta1K_uO7+github.com` is the secret then `hvv2zslMExD4s/wv0Ukl/iWMnI/lnqxcKHaOQ0MyKO8/` would be the password on github.
