import numpy as np
import matplotlib.pyplot as plt
from sklearn.preprocessing import PolynomialFeatures
from sklearn.linear_model import LinearRegression

# Sample data: FSR output voltage and corresponding weight in grams
fsr_output=np.array([3.04, 3.13, 3.33, 3.49, 3.60, 3.68, 3.77, 3.86, 3.91, 3.96, 4.1, 4.15, 4.23, 4.36, 4.41, 4.43, 4.48, 4.54, 4.59, 4.17, 4.34, 4.37, 4.45, 4.49, 4.56, 4.6, 4.62, 4.66, 4.67, 4.69, 4.7, 4.73, 4.75, 4.77, 4.78, 4.79, 4.794, 4.8, 4.8])  # Example FSR output (average ADC value)
weights = np.array([25, 33, 42, 50, 58, 67, 75, 84, 92, 101, 109, 117, 126, 134, 143, 151, 159, 167, 133, 142, 150, 159, 167, 175, 184, 192, 201, 209, 217, 226, 234, 242, 251, 259, 267, 276, 284, 293, 301])  # Known weights in grams

# Reshape data to fit the model
fsr_output = fsr_output.reshape(-1, 1)
weights = weights.reshape(-1, 1)

# Create polynomial features (degree 2 for quadratic regression)
poly = PolynomialFeatures(degree=2)
X_poly = poly.fit_transform(fsr_output)

# Create and fit the model
model = LinearRegression()
model.fit(X_poly, weights)

# Print the coefficients
a0 = model.intercept_[0]  # Intercept (constant term)
a1, a2 = model.coef_[0][1], model.coef_[0][2]  # Coefficients for V and V^2

print(f"Model Coefficients:")
print(f"a2 (V^2 term): {a2}")
print(f"a1 (V term): {a1}")
print(f"a0 (constant): {a0}")

# Predict using the regression model
predicted_weights = model.predict(X_poly)

# Plot the results
plt.scatter(fsr_output, weights, color='red')  # Known data
plt.plot(fsr_output, predicted_weights, color='blue')  # Model prediction
plt.xlabel('FSR Output (Voltage)')
plt.ylabel('Weight (grams)')
plt.show()