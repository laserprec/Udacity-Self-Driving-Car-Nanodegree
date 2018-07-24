# Load pickled data
import pickle
import numpy as np
import tensorflow as tf
tf.python.control_flow_ops = tf

with open('small_train_traffic.p', mode='rb') as f:
    data = pickle.load(f)

X_train, y_train = data['features'], data['labels']

# Initial Setup for Keras
from keras.models import Sequential
from keras.layers.core import Dense, Activation, Flatten

# TODO: Build the Fully Connected Neural Network in Keras Here
model = Sequential()
# Add the first input layer 32x32x3
model.add(Flatten(input_shape=(32, 32, 3)))
# Add the hidden layer that outputs 128 nodes
model.add(Dense(128))
# ReLU
model.add(Activation('relu'))
# Add output layer (5 nodes)
model.add(Dense(5))
# Add softmax layer
model.add(Activation('softmax'))

# preprocess data
X_normalized = np.array(X_train / 255.0 - 0.5 )

from sklearn.preprocessing import LabelBinarizer
label_binarizer = LabelBinarizer()
y_one_hot = label_binarizer.fit_transform(y_train)

model.compile('adam', 'categorical_crossentropy', ['accuracy'])
# TODO: change the number of training epochs to 3
history = model.fit(X_normalized, y_one_hot, nb_epoch=3, validation_split=0.2)