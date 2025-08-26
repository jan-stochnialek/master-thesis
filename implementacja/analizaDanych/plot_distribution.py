from itertools import cycle
import math
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np
import os

def load_data(filepath):
    df = pd.read_csv(filepath)
    return df

if __name__ == '__main__':
    
    
    sizes = ['997', '1024', '4001', '4096', '16001', '16384']
    distribution = ['Uniform', 'Skewed', 'Sequential', 'Normal', 'Clustered']
    
    
    for dist in distribution:
        CSV_FILEPATH = os.path.join(os.path.dirname(__file__), f'data/16384_{dist}_output.csv')
        df = pd.read_csv(CSV_FILEPATH)
        
        numeric_cols = df.select_dtypes(include='number').columns
        for col in numeric_cols:
            plt.figure(figsize=(8, 6))
            sns.histplot(df[col], bins=30)
            plt.title(f'Distribution of {dist}')
            plt.xlabel(col)
            plt.ylabel('Frequency')

            plt.show()


    
    
    data_df = load_data(CSV_FILEPATH)

    