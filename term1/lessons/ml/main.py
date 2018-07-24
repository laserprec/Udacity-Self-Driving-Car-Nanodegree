import numpy as np
import pylab as pl
from data import makeTerrainData
from drawPic import prettyPicture
from sklearn.naive_bayes import GaussianNB
from sklearn.svm import SVC
from sklearn import tree

features_train, labels_train, features_test, labels_test = makeTerrainData()

### the training data (features_train, labels_train) have both "fast" and "slow" points mixed
### in together--separate them so we can give them different colors in the scatterplot,
### and visually identify them
grade_fast = [features_train[ii][0] for ii in range(0, len(features_train)) if labels_train[ii]==0]
bumpy_fast = [features_train[ii][1] for ii in range(0, len(features_train)) if labels_train[ii]==0]
grade_slow = [features_train[ii][0] for ii in range(0, len(features_train)) if labels_train[ii]==1]
bumpy_slow = [features_train[ii][1] for ii in range(0, len(features_train)) if labels_train[ii]==1]

NB_clf = GaussianNB().fit(features_train, labels_train)
SVM_clf = SVC().fit(features_train, labels_train)
DTree_clf = tree.DecisionTreeClassifier().fit(features_train, labels_train)

### draw the decision boundary with the text points overlaid
prettyPicture(NB_clf, features_test, labels_test, 'naive_bayes.png', 50)
prettyPicture(SVM_clf, features_test, labels_test, 'SVM.png', 50)
prettyPicture(DTree_clf, features_test, labels_test, 'decision_tree.png', 50)


