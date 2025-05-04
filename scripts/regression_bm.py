
import pandas as pd
import numpy as np
import statsmodels.api as sm
import matplotlib.pyplot as plt
import os

def plot_fixed_var(df, intercept, coef_n, coef_m, coef_nm, output_folder, model_name):
    def _plot(x, y, label_x, fixed_val, fixed_log_val, fixed_name, filename):
        plt.figure(figsize=(8, 5))
        plt.scatter(x, y, s=1, alpha=0.03, color='blue', label='Data')
        x_sorted = np.sort(x)
        if fixed_name == "m":
            y_fit = intercept + coef_n * x_sorted + coef_m * fixed_log_val + coef_nm * x_sorted * fixed_log_val
        else:
            y_fit = intercept + coef_n * fixed_log_val + coef_m * x_sorted + coef_nm * fixed_log_val * x_sorted
        plt.plot(x_sorted, y_fit, color='red', label='Fitted Line')
        plt.xlabel(label_x)
        plt.ylabel("log(runtime)")
        plt.title(f"{model_name} | fixed {fixed_name} ≈ {fixed_val}")
        plt.grid(True)
        plt.legend(loc="upper left")
        plt.savefig(os.path.join(output_folder, filename), dpi=150)
        plt.close()

    for fixed_p in [2, 100]:
        log_p = np.log(fixed_p)
        slice_df = df[np.isclose(df['pattern_length'], fixed_p, atol=0.5)]
        _plot(slice_df['log_n'], slice_df['log_time'], "log(text_length)", fixed_p, log_p, "m",
              f"{model_name.lower().replace(' ', '_')}_textlen_fixed_p{fixed_p}.png")

    for fixed_t in [200, 10000]:
        log_t = np.log(fixed_t)
        slice_df = df[np.isclose(df['text_length'], fixed_t, atol=1)]
        _plot(slice_df['log_m'], slice_df['log_time'], "log(pattern_length)", fixed_t, log_t, "n",
              f"{model_name.lower().replace(' ', '_')}_patlen_fixed_t{fixed_t}.png")

def regression_bm_richer(df, output_folder):
    df['log_time'] = np.log(df['time_micro'])
    df['log_n'] = np.log(df['text_length'])
    df['log_m'] = np.log(df['pattern_length'])
    df['log_n_m'] = df['log_n'] * df['log_m']

    X = sm.add_constant(df[['log_n', 'log_m', 'log_n_m']])
    y = df['log_time']
    model = sm.OLS(y, X).fit()
    intercept, coef_n, coef_m, coef_nm = model.params

    with open(os.path.join(output_folder, "bm_richer_model_summary.txt"), 'w') as f:
        f.write("--- Richer Boyer-Moore Model Summary ---\n")
        f.write(model.summary().as_text())

    plt.figure(figsize=(8, 5))
    df['log_pred'] = model.predict(X)
    plt.scatter(df['log_n'] + df['log_m'], df['log_time'], s=1, alpha=0.03, color='blue', label='Data')
    plt.plot(df['log_n'] + df['log_m'], df['log_pred'], color='red', linestyle='none', marker='.', markersize=1.5, label='Fitted Line')
    plt.xlabel("log(n) + log(m)")
    plt.ylabel("log(runtime)")
    plt.title("Boyer-Moore Richer Regression: log(n), log(m), log(n)*log(m)")
    plt.grid(True)
    plt.legend(loc="upper left")
    plt.savefig(os.path.join(output_folder, "bm_richer_full.png"), dpi=150)
    plt.close()

    plot_fixed_var(df, intercept, coef_n, coef_m, coef_nm, output_folder, "Richer Boyer-Moore")

def regression_bm_simple(df, output_folder):
    df['log_time'] = np.log(df['time_micro'])
    df['log_n'] = np.log(df['text_length'])
    df['log_m'] = np.log(df['pattern_length'])
    df['log_n_times_m'] = np.log(df['text_length'] * df['pattern_length'])

    X = sm.add_constant(df[['log_n_times_m']])
    y = df['log_time']
    model = sm.OLS(y, X).fit()
    intercept, slope = model.params

    with open(os.path.join(output_folder, "bm_simple_model_summary.txt"), 'w') as f:
        f.write("--- Simple Boyer-Moore Model Summary ---\n")
        f.write(model.summary().as_text())

    plt.figure(figsize=(8, 5))
    plt.scatter(df['log_n_times_m'], df['log_time'], s=1, alpha=0.03, color='blue', label='Data')
    x_vals = np.sort(df['log_n_times_m'])
    plt.plot(x_vals, intercept + slope * x_vals, color='red', label='Fitted Line')
    plt.xlabel("log(n × m)")
    plt.ylabel("log(runtime)")
    plt.title("Boyer-Moore Simple Regression: log(n × m)")
    plt.grid(True)
    plt.legend(loc="upper left")
    plt.savefig(os.path.join(output_folder, "bm_simple_full.png"), dpi=150)
    plt.close()

    df['log_pred'] = model.predict(X)
    coef_n = coef_m = slope / 2
    coef_nm = 0
    plot_fixed_var(df, intercept, coef_n, coef_m, coef_nm, output_folder, "Simple Boyer-Moore")

if __name__ == "__main__":
    input_file = "../results/bm_results.csv"
    output_dir = "../results/bm/"
    os.makedirs(output_dir, exist_ok=True)
    data = pd.read_csv(input_file)

    regression_bm_simple(data.copy(), output_dir)
    regression_bm_richer(data.copy(), output_dir)
