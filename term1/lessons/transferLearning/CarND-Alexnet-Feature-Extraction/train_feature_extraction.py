import pickle
import time
import tensorflow as tf
from sklearn.model_selection import train_test_split
from sklearn.utils import shuffle
from alexnet import AlexNet

CLASSES = 43
EPOCH = 5
BATCH_SIZE = 128

# TODO: Load traffic signs data.
with open('./traffic-signs-data/train.p', 'rb') as f:
    data = pickle.load(f)

# TODO: Split data into training and validation sets.
X_train, X_val, y_train, y_val = train_test_split(data['features'], data['labels'], test_size=0.1, random_state=0)

# TODO: Define placeholders and resize operation.
features = tf.placeholder(tf.float32, (None, 32,32,3))
labels   = tf.placeholder(tf.int64, None)
resized  = tf.image.resize_images(features, (227, 227))

# TODO: pass placeholder as first argument to `AlexNet`.
fc7 = AlexNet(resized, feature_extract=True)
# NOTE: `tf.stop_gradient` prevents the gradient from flowing backwards
# past this point, keeping the weights before and up to `fc7` frozen.
# This also makes training faster, less work to do!
fc7 = tf.stop_gradient(fc7)

# TODO: Add the final layer for traffic sign classification.
fc7_shape = fc7.get_shape().as_list()[-1]
fc8W = tf.Variable(tf.truncated_normal((fc7_shape, CLASSES))) 
fc8b = tf.Variable(tf.zeros(CLASSES))

# TODO: Define loss, training, accuracy operations.
# HINT: Look back at your traffic signs project solution, you may
# be able to reuse some the code.
logits = tf.matmul(fc7, fc8W) + fc8b
cross_entropy = tf.nn.sparse_softmax_cross_entropy_with_logits(logits, labels)
loss_op = tf.reduce_mean(cross_entropy)
train_op = tf.train.AdamOptimizer().minimize(loss_op, var_list=[fc8W, fc8b])
init_op = tf.global_variables_initializer()

preds = tf.arg_max(logits, 1)
accuracy_op = tf.reduce_mean(tf.cast(tf.equal(preds, labels), tf.float32))


# TODO: Train and evaluate the feature extraction model.
def validate(X, y, sess):
    tot_acc = 0
    tot_loss = 0
    for offset in range(0, X.shape[0], BATCH_SIZE):
        end = offset + BATCH_SIZE
        X_batch = X[offset:end]
        y_batch = y[offset:end]

        loss, acc = sess.run([loss_op, accuracy_op], {features: X_batch, labels: y_batch})
        tot_loss += loss
        tot_acc  += acc

    return tot_loss/(X.shape[0]/BATCH_SIZE), tot_acc/(X.shape[0]/BATCH_SIZE)

with tf.Session() as sess:
    sess.run(init_op)

    for i in range(EPOCH):
        X_train, y_train = shuffle(X_train, y_train)
        t0 = time.time()
        for offset in range(0, X_train.shape[0], BATCH_SIZE):
            end = offset + BATCH_SIZE
            sess.run(train_op, {features: X_train[offset:end], labels: y_train[offset:end]})

        val_loss, val_acc = validate(X_val, y_val, sess)
        print("Epoch", i+1)
        print("Time: %.3f seconds" % (time.time() - t0))
        print("Validation Loss =", val_loss)
        print("Validation Accuracy =", val_acc)
        print("")