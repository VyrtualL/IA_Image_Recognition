# Digit-Recognizer MLP (from scratch in C)

A Multi-Layer Perceptron implemented from scratch in C (no ML library) that classifies handwritten digits (0–9) from `28×28` BMP images. 
SDL/SDL_image is only used to read pixels.

## Initialization

All weights are initialized with a random uniform value in `[-1, 1]`:

```text
W ~ U(-1, 1)
```

Layers: `W¹` (input→hidden1), `W²` (hidden1→hidden2), `W³` (hidden2→output). Biases `b¹`, `b²`, `b³` are initialized the same way.

## Architecture

```
Input (784)  →  Hidden 1 (100)  →  Hidden 2 (100)  →  Output (10)
   x                a¹                 a²                a³
```

Fully connected, sigmoid activation on every layer.

## Forward Propagation

For each layer:

```text
z¹ = W¹ᵀx  - b¹
a¹ = σ(z¹)

z² = W²ᵀa¹ - b²
a² = σ(z²)

z³ = W³ᵀa² - b³
a³ = σ(z³)
```

where `σ(z) = 1 / (1 + e^(-z))`.

## Loss

`y` is the one-hot target vector for the current image's label.

```text
e = y - a³
```

## Backpropagation

Output gradient signal:

```text
δ³ = a³(1 - a³) ⊙ e
```

Second hidden layer gradient signal:

```text
δ² = a²(1 - a²) ⊙ (W³δ³)
```

First hidden layer gradient signal:

```text
δ¹ = a¹(1 - a¹) ⊙ (W²δ²)
```

## Weight & Bias Updates

Learning rate `α = 0.1`. Updates are applied immediately after every single image (online SGD, no batching, no momentum).

Weight updates:

```text
W³ ← W³ + α a²(δ³)ᵀ
W² ← W² + α a¹(δ²)ᵀ
W¹ ← W¹ + α x(δ¹)ᵀ
```

Bias updates, because the implementation uses `z = weighted_sum - b`:

```text
b³ ← b³ - αδ³
b² ← b² - αδ²
b¹ ← b¹ - αδ¹
```

## Data Pipeline

**Preprocessing** — each pixel is binarized on its red channel:

```text
pixel = 0  if R < 125
pixel = 1  if R ≥ 125
```

The `28×28` image is flattened row-major into the `784`-length input vector `x`.

**Labeling convention** — training files are named `0.bmp` … `399.bmp` (`X.bmp`, `XX.bmp`, or `XXX.bmp` depending on the number of digits). The one-hot label of file `b` is `b % 10`: files `0, 10, 20, …` are digit `0`, files `1, 11, 21, …` are digit `1`, etc.

## Training Loop

- **75 epochs**, **400 images per epoch** → 30,000 forward/backward passes total.
- Pure online (single-sample) gradient descent, fixed `α = 0.1`.
- Each run retrains the whole network from scratch before predicting — no saving/loading of weights.

## Prediction

```text
ŷ = argmax_l(a³_l)
```
