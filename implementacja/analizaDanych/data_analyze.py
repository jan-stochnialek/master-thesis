from itertools import cycle
import math
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np
import os

sns.set_theme(style="whitegrid", palette="viridis")
plt.rcParams['figure.figsize'] = (12,7)
plt.rcParams['axes.titlesize'] = 16
plt.rcParams['axes.labelsize'] = 16

def load_data(filepath):
    df = pd.read_csv(filepath)
    return df
    
def print_summary_statistics(df, group_by_cols, target_col='ProbeCount'):
    
    summary = df.groupby(group_by_cols)[target_col].agg(['mean', 'std', 'max', 'median'])
    
    summary['mean'] = summary['mean'].round(3)
    summary['std'] = summary['std'].round(3)
    
    print(summary)
    
    
def plot_probe_distribution(df, hash_function, load_factor, target_col='ProbeCount', max_probes=20):
    subset = df[(df['HashFunction'] == hash_function) & (df['LoadFactor'] == load_factor)]
    
    plt.figure()
    
    sns.histplot(data=subset, x=target_col, discrete=False, stat='probability')
    
    plt.title(f'Dystrybucja prób dla funkcji {hash_function}\n i load factor = {load_factor}')
    plt.xlabel('Liczba prób / porównań per insert')
    plt.ylabel("prawdopodobieństwo")
    plt.xlim(-0.5, max_probes + 0.5)
    plt.xticks(range(0, max_probes +1))
    plt.tight_layout()
    plt.savefig(f'distribution_{hash_function}_{load_factor}.png')
    
    
    
    
if __name__ == '__main__':
    CSV_FILEPATH = os.path.join(os.path.dirname(__file__), 'data/hash_table_stats.csv')
    
    pd.read_csv(CSV_FILEPATH)
    
    data_df = load_data(CSV_FILEPATH)

    # Group by TableSize and KeyDistribution
    groups = list(data_df.groupby(["TableSize", "KeyDistribution"]))
    # Choose a colormap with many distinct colors
    colors = plt.get_cmap('tab10').colors  # 10 distinct colors
    color_cycle = cycle(colors)  # allows cycling if more than 10 lines
    # Process in chunks of 4 groups per figure

    for i in range(0, len(groups), 4):
        chunk = groups[i:i+4]
        
        fig, axes = plt.subplots(2, 2, figsize=(12, 8), squeeze=False)
        fig.suptitle(f"Plots {i+1} to {i+len(chunk)}", fontsize=14)
        
        for ax, ((table_size, key_dist), group) in zip(axes.flat, chunk):
            color_cycle = cycle(colors)  # reset for each subplot
            
            for (hash_func, probing), subgrp in group.groupby(["HashFunction", "ProbingStrategy"]):
                subgrp_sorted = subgrp.sort_values(by="LoadFactor")
                
                # Interpolate for smooth line
                x = subgrp_sorted["LoadFactor"].values
                y = subgrp_sorted["ProbeCount"].values
                x_smooth = np.linspace(x.min(), x.max(), 200)
                y_smooth = np.interp(x_smooth, x, y)
                
                ax.plot(x_smooth, y_smooth, color=next(color_cycle), label=f"{hash_func}, {probing}", linewidth=2)
            
            ax.set_title(f"TableSize={table_size}, KeyDist={key_dist}")
            ax.set_xlabel("Load Factor")
            ax.set_ylabel("Probe Count")
            ax.grid(True)
            ax.legend(fontsize='small')
        
        for ax in axes.flat[len(chunk):]:
            ax.set_visible(False)
        
        plt.tight_layout(rect=[0, 0, 1, 0.96])
        plt.show()