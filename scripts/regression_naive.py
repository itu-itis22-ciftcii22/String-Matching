import pandas as pd
import statsmodels.api as sm
import os
import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D

def regression_and_3d_plot(csv_file, output_folder):
    df = pd.read_csv(csv_file)

    # Log-transform the inputs and target
    df['log_text_length'] = np.log(df['text_length'])
    df['log_pattern_length'] = np.log(df['pattern_length'])
    df['log_time_micro'] = np.log(df['time_micro'])

    # Prepare features and target
    X = df[['log_text_length', 'log_pattern_length']]
    X = sm.add_constant(X)
    y = df['log_time_micro']

    # Fit the linear model
    model = sm.OLS(y, X).fit()

    # Save model summary
    output_text_path = os.path.join(output_folder, "regression_summary.txt")
    with open(output_text_path, 'w') as f:
        f.write("--- Regression Summary ---\n")
        f.write(model.summary().as_text())

    # Extract coefficients
    intercept, coef_x, coef_y = model.params
    print(f"Model: log(time) = {intercept:.4f} + {coef_x:.4f}*log(n) + {coef_y:.4f}*log(m)")

    # 3D scatter + surface
    fig = plt.figure(figsize=(12, 8))
    ax = fig.add_subplot(111, projection='3d')

    x_vals = df['log_text_length']
    y_vals = df['log_pattern_length']
    z_vals = df['log_time_micro']

    ax.scatter(x_vals, y_vals, z_vals, c='blue', alpha=0.05, label='Data')

    # Create a meshgrid for surface
    x_surf, y_surf = np.meshgrid(
        np.linspace(x_vals.min(), x_vals.max(), 50),
        np.linspace(y_vals.min(), y_vals.max(), 50)
    )
    z_surf = intercept + coef_x * x_surf + coef_y * y_surf
    ax.plot_surface(x_surf, y_surf, z_surf, alpha=0.4, color='red', edgecolor='none')

    ax.set_xlabel('log(text_length)')
    ax.set_ylabel('log(pattern_length)')
    ax.set_zlabel('log(runtime)')
    ax.set_title('Log-Log Regression Surface over Data')

    output_plot_path = os.path.join(output_folder, "regression_3d_plot.png")
    plt.savefig(output_plot_path, dpi=150)
    plt.close()

    print("Completed analysis and plot saved.")

# Example usage
if __name__ == '__main__':
    input_file = "../results/naive_results.csv"
    output_folder = "../results/"
    os.makedirs(output_folder, exist_ok=True)
    regression_and_3d_plot(input_file, output_folder)

