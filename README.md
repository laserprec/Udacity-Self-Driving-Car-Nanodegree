# Udacity Self-Driving Car Nanodegree

This repository contains my implementation to Udacity Self-Driving Car Nanodegree projects, some personal note keeping, and useful bash scripts to spin up the working environment quickly.

The entire Nanodegree is broken down into 3 terms. You can find the individual project repository for each term under the `term1/projects` for example.

## Term 1

### Miniconda Environment

1. Activate

    ```
    source activate carnd-term1 
    ```

2. Deactivate

    ```
    source deactivate
    ```

### Docker Environment

1. Running the term1 starter kit

    ```
    docker run -it --rm -p 8888:8888 -v `pwd`:/src udacity/carnd-term1-starter-kit
    ```


