import pandas as pd
import statsmodels.api as sm
import glob2
import os
from joblib import Parallel, delayed

def prepare_data(df):
    df['text_pattern_mult'] = df['text_length'] * df['pattern_length']
    return df

def regression_analysis(csv_file, output_folder):
    algorithm_name = os.path.splitext(os.path.basename(csv_file))[0]
    df = pd.read_csv(csv_file)
    df = prepare_data(df)

    X = df[['text_length', 'pattern_length', 'text_pattern_mult']]
    y = df['time_cpu']

    X = sm.add_constant(X)

    model = sm.OLS(y, X).fit()

    output_path = os.path.join(output_folder, f"{algorithm_name}_regression_summary.txt")

    with open(output_path, 'w') as f:
        f.write(f"--- Regression results for algorithm: {algorithm_name} ---\n")
        f.write(model.summary().as_text())

    print(f"Completed analysis for: {algorithm_name}")

def analyze_algorithms_separately_parallel(input_folder, output_folder):
    os.makedirs(output_folder, exist_ok=True)
    csv_files = glob2.glob(os.path.join(input_folder, '*.csv'))

    Parallel(n_jobs=-1)(
        delayed(regression_analysis)(csv_file, output_folder) for csv_file in csv_files
    )

# Example Usage:
if __name__ == '__main__':
    input_folder = "../results/"
    output_folder = "../results/"

    analyze_algorithms_separately_parallel(input_folder, output_folder)



