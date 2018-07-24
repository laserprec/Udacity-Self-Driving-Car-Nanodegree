import tensorflow as tf
# Recall the formula for calculating the new height or width:
# new_height = (input_height - filter_height + 2 * P)/S + 1
# new_width = (input_width - filter_width + 2 * P)/S + 1

input = tf.placeholder(tf.float32, (None, 32, 32, 3))
filter_weights = tf.Variable(tf.truncated_normal((8, 8, 3, 20))) # (height, width, input_depth, output_depth)
filter_bias = tf.Variable(tf.zeros(20))
strides = [1, 2, 2, 1] # (batch, height, width, depth)
padding = 'SAME'
conv = tf.nn.conv2d(input, filter_weights, strides, padding) + filter_bias

# In summary TensorFlow uses the following equation for 'SAME' vs 'VALID'

# SAME Padding, the output height and width are computed as:
# out_height = ceil(float(in_height) / float(strides[1]))
# out_width = ceil(float(in_width) / float(strides[2]))

# VALID Padding, the output height and width are computed as:
# out_height = ceil(float(in_height - filter_height + 1) / float(strides[1]))
# out_width = ceil(float(in_width - filter_width + 1) / float(strides[2]))