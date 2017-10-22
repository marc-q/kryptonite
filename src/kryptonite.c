/*
 * kryptonite.c
 * Copyright (C) 2017  Marc Volker Dickmann
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

//
// Step one: Generate a one way hash to prevent leaking the original password
//

static unsigned char *
kry_hash (unsigned char *out,
          unsigned int  *out_len,
          const char    *in)
{
	// Use SHA256
	OpenSSL_add_all_digests ();
	
	const EVP_MD *md = EVP_sha256 ();
	
	if (!md)
		return NULL;
	
	// Create an Message Digest Context
	EVP_MD_CTX *mctx = EVP_MD_CTX_create ();
	EVP_DigestInit_ex (mctx, md, NULL);
	
	// Store the hash of @in in @out
	EVP_DigestUpdate (mctx, in, strlen (in));
	EVP_DigestFinal_ex (mctx, out, out_len);
	
	// Cleanup
	EVP_MD_CTX_destroy (mctx);
	EVP_cleanup ();
	return out;
}

//
// Step two: Encode Krypton so it can be entered by keyboard
//
// WARNING: YOU HAVE TO MAKE YOUR OWN CUSTOM ENCODING FUNCTION!
//          THIS IS ONLY AN EXAMPLE!
//

static char *
kry_encode (char                *out,
            const unsigned char *in,
            const unsigned int   in_len)
{
	// Encode with Base64
	long v;
	
	for (unsigned int i = 0; i < in_len; i += 4)
	{
		v = (in[i] |
		     (in[i + 1] << 8) |
		     (in[i + 2] << 16) |
		     (in[i + 3] << 24));
		
		strcat (out, l64a (v));
	}
	return out;
}

//
// CLI
//

static void
usage (void)
{
	printf ("Usage: kryptonite <pw>!\n\n"
	        "<pw> could be any format f.e. 8 chars + domain\n"
	        "Example: Ta1K_uO7+github.com\n\n"
	        "In order to generate secure Kryptons you have\n"
	        "to implement your own custom encode function.\n");
	exit (EXIT_FAILURE);
}

int
main (int argc, char* argv[])
{
	if (argc != 2)
		usage ();
	
	// Warn about the custom encoding function
	printf ("\nWARNING: YOU NEED TO IMPLEMENT YOUR OWN CUSTOM ENCODING "
	        "FUNCTION!\n\n");
	
	// Generate a hash
	unsigned char hash[EVP_MAX_MD_SIZE];
	unsigned int hash_len = 0;
	
	kry_hash (hash, &hash_len, argv[1]);
	
	// Encode the hash
	char krypton[EVP_MAX_MD_SIZE + (EVP_MAX_MD_SIZE / 3)] = "";
	
	kry_encode (krypton, hash, hash_len);
	
	// Print Krypton
	printf ("PW:\t\t%s\nKrypton:\t%s\n", argv[1], krypton);
	return 0;
}
