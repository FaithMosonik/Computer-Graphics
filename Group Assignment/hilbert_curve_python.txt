import numpy as np
import matplotlib.pyplot as plt
import os

# List to store points of the Hilbert curve
hilbert_curve_points = []

# Function to recursively generate the Hilbert curve points
def hilbert_curve(order, x, y, xi, xj, yi, yj):
    if order <= 0:
        px = x + (xi + yi) / 2
        py = y + (xj + yj) / 2
        hilbert_curve_points.append((px, py))
    else:
        hilbert_curve(order - 1, x, y, yi / 2, yj / 2, xi / 2, xj / 2)
        hilbert_curve(order - 1, x + xi / 2, y + xj / 2, xi / 2, xj / 2, yi / 2, yj / 2)
        hilbert_curve(order - 1, x + xi / 2 + yi / 2, y + xj / 2 + yj / 2, xi / 2, xj / 2, yi / 2, yj / 2)
        hilbert_curve(order - 1, x + xi / 2 + yi, y + xj / 2 + yj, -yi / 2, -yj / 2, -xi / 2, -xj / 2)

def save_figure(fig, order):
    # Default filename
    default_filename = f"hilbert_curve_order_{order}.png"
    
    # Check if file already exists
    count = 1
    filename = default_filename
    while os.path.exists(filename):
        filename = f"hilbert_curve_order_{order}_{count}.png"
        count += 1
    
    # Save the figure
    fig.savefig(filename, facecolor='black', bbox_inches='tight')
    print(f"Image saved as '{filename}' in the current directory.")

def main():
    # Clear any existing points
    global hilbert_curve_points
    hilbert_curve_points = []
    
    # Set the order of the Hilbert curve
    order = 5
    
    # Allow user to specify order
    try:
        user_order = input("Enter the order of the Hilbert curve (1-7) [default=5]: ")
        if user_order.strip():
            order = int(user_order)
            # Limit order to reasonable range
            if order < 1:
                print("Order too small, using minimum order 1.")
                order = 1
            elif order > 7:
                print("Order too large (may be slow), using maximum order 7.")
                order = 7
    except ValueError:
        print("Invalid input, using default order 5.")
    
    print(f"Generating Hilbert curve of order {order}...")
    
    # Generate Hilbert curve points
    hilbert_curve(order, -0.9, -0.9, 1.8, 0.0, 0.0, 1.8)
    
    # Convert list of points to numpy arrays for plotting
    points = np.array(hilbert_curve_points)
    x, y = points[:, 0], points[:, 1]
    
    # Create figure with equal aspect ratio
    fig = plt.figure(figsize=(8, 8), facecolor='black')
    ax = plt.gca()
    ax.set_facecolor('black')
    
    # Set equal aspect ratio to ensure proper proportions
    ax.set_aspect('equal')
    
    # Draw the axes with calibrations
    ax.axhline(y=0, color='white', linestyle='-', alpha=0.7)
    ax.axvline(x=0, color='white', linestyle='-', alpha=0.7)
    
    # Set up axis ticks and labels
    tick_positions = np.arange(-1.0, 1.1, 0.2)
    ax.set_xticks(tick_positions)
    ax.set_yticks(tick_positions)
    ax.set_xticklabels([f"{x:.1f}" for x in tick_positions], color='white')
    ax.set_yticklabels([f"{y:.1f}" for y in tick_positions], color='white')
    
    # Customize tick appearance
    ax.tick_params(axis='both', colors='white', direction='out', length=5)
    
    # Add grid for better visualization of calibrations
    ax.grid(True, linestyle='--', alpha=0.3, color='gray')
    
    # Label the axes
    ax.set_xlabel("X-axis", color='white', fontsize=12)
    ax.set_ylabel("Y-axis", color='white', fontsize=12)
    
    # Plot the Hilbert curve
    plt.plot(x, y, 'r-', linewidth=1.5)
    
    # Set the limits of the plot exactly the same for both axes
    plt.xlim(-1.0, 1.0)
    plt.ylim(-1.0, 1.0)
    
    # Add a title
    plt.title(f"Hilbert Curve (Order {order})", color='white', fontsize=14)
    
    # Display the plot with proper spacing
    plt.tight_layout()
    
    # Show the plot
    plt.show()
    
    # Ask user if they want to save the image
    save_option = input("Do you want to save this image? (y/n): ").strip().lower()
    if save_option == 'y' or save_option == 'yes':
        save_figure(fig, order)
    else:
        print("Image not saved.")

if __name__ == "__main__":
    main()