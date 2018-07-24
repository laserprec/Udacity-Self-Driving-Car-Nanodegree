"""
Capture Lane Lines by Combining Different Gradient Thresholds
"""
import numpy as np
import cv2
import matplotlib.pyplot as plt
import matplotlib.image as mpimg

KERNEL = 17
GRAD_X_MAX = 255
GRAD_X_MIN = 15
GRAD_Y_MAX = 255
GRAD_Y_MIN = 15
MAG_MAX = 150
MAG_MIN = 65
DIR_MAX = 1.5
DIR_MIN = 0.4

def mag_thresh(img, sobel_kernel=3, mag_thresh=(0, 255)):
    # Calculate gradient magnitude
    gray = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)
    sobelx = cv2.Sobel(gray, cv2.CV_64F, 1, 0, ksize=sobel_kernel)
    sobely = cv2.Sobel(gray, cv2.CV_64F, 0, 1, ksize=sobel_kernel)
    gradmag = np.sqrt(sobelx**2 + sobely**2)
    scale_factor = np.max(gradmag)/255 
    gradmag = (gradmag/scale_factor).astype(np.uint8) 
    mag_binary = np.zeros_like(gradmag)
    mag_binary[(gradmag >= mag_thresh[0]) & (gradmag <= mag_thresh[1])] = 1
    return mag_binary

def abs_sobel_thresh(img, orient='x', sobel_kernel=3, thresh=(0, 255)):
    # Calculate directional gradient
    gray = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)
    sobel = cv2.Sobel(gray, cv2.CV_64F, int(orient == 'x'), int(orient != 'x'))
    abs_sobel = np.absolute(sobel)
    scaled_sobel = np.uint8(255*abs_sobel/np.max(abs_sobel))  
    grad_mask = np.zeros_like(scaled_sobel)
    grad_mask[(scaled_sobel >= thresh[0]) & (scaled_sobel <= thresh[1])] = 1
    return grad_mask

def dir_threshold(img, sobel_kernel=3, thresh=(0, np.pi/2)):
    # Calculate gradient direction
    gray = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)
    sobelx = cv2.Sobel(gray, cv2.CV_64F, 1, 0, ksize=sobel_kernel)
    sobely = cv2.Sobel(gray, cv2.CV_64F, 0, 1, ksize=sobel_kernel) 
    # 3) Take the absolute value of the x and y gradients
    # 4) Use np.arctan2(abs_sobely, abs_sobelx) to calculate the direction of the gradient 
    gradDirect = np.arctan2(np.absolute(sobely), np.absolute(sobelx))
    # 5) Create a binary mask where direction thresholds are met
    dir_mask = np.zeros_like(gradDirect)
    # 6) Return this mask as your binary_output image
    dir_mask[(thresh[0] < gradDirect) & (gradDirect < thresh[1])] = 1
    return dir_mask

image = mpimg.imread('signs_vehicles_xygrad.jpg')

# Apply each of the thresholding functions
gradx = abs_sobel_thresh(image, orient='x', sobel_kernel=KERNEL, thresh=(GRAD_X_MIN, GRAD_X_MAX))
grady = abs_sobel_thresh(image, orient='y', sobel_kernel=KERNEL, thresh=(GRAD_Y_MIN, GRAD_Y_MAX))
mag_binary = mag_thresh(image, sobel_kernel=KERNEL, mag_thresh=(MAG_MIN, MAG_MAX))
dir_binary = dir_threshold(image, sobel_kernel=KERNEL, thresh=(DIR_MIN, DIR_MAX))

# Combining thresholds
combined = np.zeros_like(dir_binary)
combined[((gradx == 1) & (grady == 1)) & ((mag_binary == 1) & (dir_binary == 1))] = 1

f, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 4))
f.tight_layout()
ax1.imshow(image)
ax1.set_title('Original Image', fontsize=24)
ax2.imshow(combined, cmap='gray')
ax2.set_title('Thresholded Gradient', fontsize=24)
plt.subplots_adjust(left=0., right=1, top=0.9, bottom=0.)
plt.show()