"""
Very basic exrpimental implementation of the Lampart signature algorithm
"""

import secrets, hashlib

def sha256sum(message):
	"""
	Find the SHA256 sum of a message
	"""
	
	h = hashlib.sha256()
	h.update(message)
	return h.digest()

def inttobytes(number):
	"""
	Convert an integer to bytes
	"""
	
	return number.to_bytes(32, 'big')

def bitat(a, i):
	"""
	Return the bit of a at i (0 or 1)
	"""
	
	return (int.from_bytes(a, 'big') & (1 << i)) >> i

def roll_key():
	"""
	Roll a public-private key pair
	"""
	
	private = []
	
	# Generate the 512 private numbers. We need to make a decision on which numbers
	# to publicly release later for each bit of the hash of the message we'd like
	# to sign. 
	for i in range(512):
		private.append(inttobytes(secrets.randbits(256)))
	
	public = []
	
	# Find the hashes of these numbers, which we can safely reveal since by
	# definition of the hash function we cannot find the numbers easily
	for i in range(512):
		public.append(sha256sum(private[i]))
	
	# We can now return this as a public and private key pair
	return (private, public)

def sign(private, message):
	"""
	Sign a message (it's hash is taken first)
	"""
	
	hash = sha256sum(message)
	
	signature = []
	
	# Selectively pick the numbers that we would like to reveal such that they
	# coreespond to the bits of the hash of the message. A person can later
	# select the appropraite public hashes using the hash of the message and 
	# compare them to the hash of the private numbers that we have revealed.
	# If everything is the same, then this message must have been signed.
	for i in range(256):
		signature.append(private[(2 * i) + bitat(hash, i)])
	
	return signature

def verify(public, signature, message):
	"""
	Verify a message given the public key, signature and message
	"""
	
	hash = sha256sum(message)
	
	selected = []
	
	# First, we need to select which parts of the public key we want to compare
	# to based on the hash of the message.
	for i in range(256):
		selected.append(public[(2 * i) + bitat(hash, i)])
	
	# Next, we need to take the hashes of the signature values.
	for i in range(256):
		signature[i] = sha256sum(signature[i])
	
	# Finally, we need to make sure everything is the same
	for i in range(256):
		if (signature[i] != selected[i]):
			return False
	
	return True

def main():
	message = b"Yes, I do quite enjoy the new video game that came out today(!)"
	
	print("Message:", message)
	
	keys = roll_key()
	
	print("Keys:", keys)
	
	sig = sign(keys[0], message)
	
	print("Signature:", sig)
	
	okay = verify(keys[1], sig, message)
	
	print("Okay:", okay)

if (__name__ == "__main__"):
	main()
