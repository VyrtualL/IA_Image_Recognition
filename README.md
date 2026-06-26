# Digit-Recognizer MLP (from scratch in C)

A Multi-Layer Perceptron implemented from scratch in C (no ML library) that classifies handwritten digits (0 to 9) from `28×28` BMP images. 
SDL/SDL_image is only used to read pixels.

## Initialization

All weights are initialized with a random uniform value in `[-1, 1]` :
Biases `b¹`, `b²`, `b³` are initialized the same way.

```text
W ~ U(-1, 1)
```

## Network Architecture

A fully-connected feedforward network with 2 hidden layers :

```
Input Layer        Hidden Layer 1      Hidden Layer 2      Output Layer
  784 neurons   →    100 neurons    →    100 neurons    →   10 neurons
 (28×28 image)        (sigmoid)           (sigmoid)          (sigmoid)
```

| Layer | Size | Weight matrix to next layer | Bias vector |
|---|---|---|---|
| Input | 784 | `w_i_h[784][100]` | — |
| Hidden 1 | 100 | `w_h_h[100][100]` | `b_f_h[100]` |
| Hidden 2 | 100 | `w_h_o[100][10]` | `b_s_h[100]` |
| Output | 10 | — | `b_o_l[10]` |

## Forward Propagation

For each layer :

```text
z¹ = W¹ᵀx  - b¹
a¹ = σ(z¹)

z² = W²ᵀa¹ - b²
a² = σ(z²)

z³ = W³ᵀa² - b³
a³ = σ(z³)
```

where `σ(z) = 1 / (1 + e^(-z))`.

## Loss Function

The target vector `error_wanted` is a one-hot encoding of the digit label (ex : digit `3` → `[0,0,0,1,0,0,0,0,0,0]`).

The per-output error used on my code is simply :

```text
error_k = t_k - o_k
```

where `t_k` is the target and `o_k` the network's output for class `k`. Propagated through the sigmoid derivative, this corresponds to minimizing the classic **sum-of-squared-error (SSE)** loss :

```text
E = 1/2 * Σ_k (t_k - o_k)²
```

This is the loss implicitly used by the **generalized delta rule** (Widrow–Hoff rule generalized to multilayer networks), as opposed to the **categorical cross-entropy** loss that is the standard pairing with a true softmax output :

```text
L_cross_entropy = - Σ_k  t_k * log(o_k)
```

Cross-entropy + softmax is the modern standard for classification because the loss directly models a probability distribution over classes. 
I used quared error + sigmoid because it is the original formulation used in Rumelhart, Hinton & Williams' 1986 backpropagation paper (it works, but converges less clean for multi-class problems than softmax + cross-entropy).

## Backpropagation

Output gradient signal :

```text
δ³ = a³(1 - a³) ⊙ e
```

Second hidden layer gradient signal :

```text
δ² = a²(1 - a²) ⊙ (W³δ³)
```

First hidden layer gradient signal :

```text
δ¹ = a¹(1 - a¹) ⊙ (W²δ²)
```

## Weight & Bias Updates

Learning rate `α = 0.1`.

Weight updates :

```text
W³ ← W³ + α a²(δ³)ᵀ
W² ← W² + α a¹(δ²)ᵀ
W¹ ← W¹ + α x(δ¹)ᵀ
```

Bias updates :

```text
b³ ← b³ - αδ³
b² ← b² - αδ²
b¹ ← b¹ - αδ¹
```

## Training Loop

- **75 epochs**, **400 images per epoch** → 30,000 forward/backward passes total.

## File Structure

| File | Role |
|---|---|
| `main.c` | Entry point : initializes weights/biases, calls `gen()` to train, loads the target image, runs a final forward pass, prints the prediction. |
| `ite.c` | `ite()` One full training iteration : forward pass, error computation, backpropagation (gradients), and weight/bias updates for a single image. |
| `init.c` | Weight/bias random initialization functions (`init_weight_w_i_h`, `init_weight_w_h_h`, `init_weight_w_h_o`, `init_b_h`, `init_b_o`). |
| `gen.c` | SDL/SDL_image plumbing (`load_image`, `get_pixel`), `init_input_layer()` to turn a BMP into the 784-float input vector, and `gen()`, the main training loop over the dataset. |

## Build & Run

The code targets **SDL 1.2** (`#include <SDL/SDL.h>`). On Debian/Ubuntu :

```bash
sudo apt-get install libsdl1.2-dev libsdl-image1.2-dev
gcc main.c ite.c init.c gen.c -o mlp $(sdl-config --cflags --libs) -lSDL_image -lm
```

Run (the program trains first, then classifies the given image) :

```bash
./mlp path/to/digit.bmp
```
