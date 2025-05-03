import os
import random
import string
import numpy as np

# Configuration
output_dir = '../data'
text_file = os.path.join(output_dir, 'sample_texts.txt')
pattern_file = os.path.join(output_dir, 'test_patterns.txt')

text_lengths = np.linspace(200, 10000, 50, dtype=int).tolist()
pattern_lengths = np.linspace(2, 100, 50, dtype=int).tolist()

samples_per_length = 50
pattern_per_length = 50

# Ensure output directory exists
os.makedirs(output_dir, exist_ok=True)

# Storage for pairing text and its patterns
all_texts = []
all_patterns = []

# Generate texts and patterns
text_id = 1

with open(text_file, 'w') as tf, open(pattern_file, 'w') as pf:
    for t_len in text_lengths:
        for _ in range(samples_per_length):
            # Generate text
            text = ''.join(random.choices(string.ascii_lowercase + ' ', k=t_len))
            tf.write(f"---{text_id}---\n{text}\n")
            all_texts.append(text)

            # Generate 50 patterns for each p_len from the current text
            for p_len in pattern_lengths:
                for _ in range(pattern_per_length):
                    if p_len <= len(text):
                        start = random.randint(0, len(text) - p_len)
                        pattern = text[start:start + p_len]
                    else:
                        # fallback if pattern too long
                        pattern = ''.join(random.choices(string.ascii_lowercase, k=p_len))
                    pf.write(f"---{text_id}---\n{pattern}\n")

            text_id += 1

