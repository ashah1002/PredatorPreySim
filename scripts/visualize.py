import pandas as pd
import matplotlib.pyplot as plt
import sys

if len(sys.argv) > 1:
    path = sys.argv[1]
else:
    raise ValueError("No path provided")

df = pd.read_csv(path)

df['cumulative_time'] = 0.0
cumulative_offset = 0.0

for gen in sorted(df['generation'].unique()):
    gen_mask = df['generation'] == gen
    gen_data = df[gen_mask]
    
    df.loc[gen_mask, 'cumulative_time'] = gen_data['time'] + cumulative_offset
    cumulative_offset += gen_data['time'].max()

# Plot predators and prey over cumulative time
fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(14, 10))

# Main population plot
ax1.plot(df['cumulative_time'], df['predators'], 'r-', linewidth=2, label='Predators')
ax1.plot(df['cumulative_time'], df['prey'], 'b-', linewidth=2, label='Prey')

# Add vertical lines at generation boundaries
for gen in sorted(df['generation'].unique())[1:]:
    gen_start_time = df[df['generation'] == gen]['cumulative_time'].iloc[0]
    ax1.axvline(x=gen_start_time, color='gray', linestyle='--', alpha=0.5, linewidth=1)

ax1.set_xlabel('Time (Cumulative across Generations)', fontsize=12)
ax1.set_ylabel('Population Size', fontsize=12)
ax1.legend(fontsize=12)
ax1.grid(True, alpha=0.3)
ax1.set_title(f'Predator-Prey Population: {df["generation"].max()} Generations (Seed 42)', fontsize=14)

# Generation-level summary plot (start and end of each generation)
gen_summary = df.groupby('generation').agg({
    'predators': ['first', 'last'],
    'prey': ['first', 'last'],
    'cumulative_time': ['first', 'last']
}).reset_index()

gen_summary.columns = ['generation', 'pred_start', 'pred_end', 'prey_start', 'prey_end', 'time_start', 'time_end']

# Plot generation endpoints
ax2.plot(gen_summary['generation'], gen_summary['pred_start'], 'ro-', label='Predators (start)', markersize=8)
ax2.plot(gen_summary['generation'], gen_summary['pred_end'], 'rs--', label='Predators (end)', markersize=8, alpha=0.6)
ax2.plot(gen_summary['generation'], gen_summary['prey_start'], 'bo-', label='Prey (start)', markersize=8)
ax2.plot(gen_summary['generation'], gen_summary['prey_end'], 'bs--', label='Prey (end)', markersize=8, alpha=0.6)

ax2.set_xlabel('Generation', fontsize=12)
ax2.set_ylabel('Population Size', fontsize=12)
ax2.legend(fontsize=10)
ax2.grid(True, alpha=0.3)
ax2.set_title('Population at Start/End of Each Generation', fontsize=14)

plt.tight_layout()
plt.savefig(path.replace('.csv', '.png'), dpi=150)
print(f"Plot saved to: {path.replace('.csv', '.png')}")

# Summary statistics by generation
print("\nGeneration Summary:")
print("=" * 80)
summary = df.groupby('generation').agg({
    'predators': ['mean', 'min', 'max', 'first', 'last'],
    'prey': ['mean', 'min', 'max', 'first', 'last']
})
print(summary)

# Overall statistics
print("\n\nOverall Statistics:")
print("=" * 80)
print(f"Total time simulated: {df['cumulative_time'].max():.1f}")
print(f"Number of generations: {df['generation'].max()}")
print(f"\nPredators - Start: {df['predators'].iloc[0]}, End: {df['predators'].iloc[-1]}")
print(f"Prey - Start: {df['prey'].iloc[0]}, End: {df['prey'].iloc[-1]}")