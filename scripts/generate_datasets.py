import os
import random
import string

# Configuration
output_dir = '../data'
text_file = os.path.join(output_dir, 'sample_texts.txt')
pattern_file = os.path.join(output_dir, 'test_patterns.txt')
num_samples = 10
text_lengths = [100, 500, 1000, 5000, 10000]
pattern_lengths = [3, 5, 10, 20]

# Ensure output directory exists
os.makedirs(output_dir, exist_ok=True)

# Generate sample texts
with open(text_file, 'w') as tf:
    for i in range(num_samples):
        length = random.choice(text_lengths)
        text = ''.join(random.choices(string.ascii_lowercase + ' ', k=length))
        tf.write(f"---TEXT {i+1}---\n{text}\n")

# Generate test patterns
with open(pattern_file, 'w') as pf:
    for i in range(num_samples):
        length = random.choice(pattern_lengths)
        pattern = ''.join(random.choices(string.ascii_lowercase, k=length))
        pf.write(f"---PATTERN {i+1}---\n{pattern}\n")
