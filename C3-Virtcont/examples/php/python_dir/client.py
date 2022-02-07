import redis
import string

r = redis.Redis(host="myredis")

# Read the full file
with open("getp.txt") as f:
    data=f.read()

# This will eventually contain
# all words
words = []

# Split on lines
lines=data.split("\n")

# Iterate on lines
for l in lines:
    # This hack removes puntuation
    l = l.translate(str.maketrans('', '', string.punctuation))
    # Now split on spaces
    words += l.split(" ")

# This will add all words to the redis
for w in words:
    print(w)
    r.hincrby("words", w, 1)
