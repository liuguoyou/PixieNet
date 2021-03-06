![PixieNetLogo](images/PixieBlueLogoSmallTransparent.png)
# PixieNet

A binary convolutional neural network framework for iOS devices

### Team Members

**[Esha Uboweja](http://https://github.com/eknight7)** (euboweja) and **[Salvador Medina](https://github.com/salmedina)** (salvadom)

## Checkpoint

### Revised Schedule

#### Task Breakdown

1. ~~Profile the [TensorFlow iOS camera application](https://github.com/tensorflow/tensorflow/tree/master/tensorflow/contrib/ios_examples) (Both)~~
  1. ~~Investigate other iOS CNN implementations (DeepLearningKit, BNNs)~~
  1. ~~Review literature on XNOR nets and Binary networks (and their math)~~
2. Build application carcass for development (Salvador)
3. (Prototype) Implement a forward pass by an XNOR-Net.(Both)
  1. Modularize the forward pass
  1. Implement the atomic components
  1. Test the components
4. (on iOS Device) Implement the fully running XNOR-Net with VGGNet or AlexNet architecture. (Both)
5. Build the profiling tasks for optimization. (Esha)
6. Optimize the slowest/most expensive components through CPU/GPU frameworks and libraries and algorithm tricks learnt in class. (Both)
7. Compare and analyze the implementation. (Salvador)
8. Improve application UI (controls, interface). (Esha)
9. Design and implement a real-use case scenario for the implemented net. (Both)
10. Make the demo video. (Both)

#### Hard Deadlines

1. ~~Mid-project Checkpoint: 16 November, 2016~~
2. Project Demo: 8 December, 2016
3. Final Project Report: 11 December 2016

#### Calendar

| Date             | Description                    |
|------------------|:------------------------------:|
| 21 November 2016 | Finish Task 2,3                |
| ~~24 November 2016~~ | ~~Profiling completed~~        |
| 24 November 2016 | Finish Task 4                  |
| 28 November 2016 | Finish Tasks 5, 6, 7           |
|  1 December 2016 | Finish Task 8                  |
|  5 December 2016 | Finish Task 9, 10              |
|  7 December 2016 | Fully developed application    |


## Project Proposal

### Summary

We aim to implement a binary convolutional neural network capable of being executed on an iOS device to run image classification on image frames captured by the device's camera.

![Is that a bird?!](images/tasks_xkcd_1425.png)

Performing image detection on a mobile device ([source](http://xkcd.com/1425/))

### Background

* **Why is this a mobile device application project?**

Convolutional neural networks (CNNs) work really well in tasks like object recognition and scene classification, and for building image embeddings (vectorial or feature representations) that can in turn be used in more complex tasks such as scene navigation, obstacle avoidance etc.

Presently, there are many popular libraries and frameworks for deep learning such as Google's TensorFlow, Facebook's Torch, Caffe, Theano etc. There are iOS versions of some of these frameworks, such as TensorFlow and Torch. We examined an application published in the TensorFlow repository ([Object detection via the camera app](https://github.com/tensorflow/tensorflow/tree/master/tensorflow/contrib/ios_examples)) wherein a pre-trained [GoogleLeNet](http://static.googleusercontent.com/media/research.google.com/en//pubs/archive/43022.pdf) model (size approx. 50 MB) was able to perform object recognition on a video on our iPad Air 2 at 6.8 FPS. This is a decent speed because the application is able to perform real time object recognition on the iOS device. However, when we tried to change the application code to use a pre-trained VGG-16 Network (trained on 1001 classes of ImageNet dataset) instead, the application crashed due to the huge size of the weights file (approx. 553.5 MB). 

_Simply put, there is a problem of a huge memory footprint of many existing deep networks._

The ability of running such networks on mobile devices can help in research projects and applications. For instance, a high performance and accurate object/scene classifier can be used to guide the visually impaired, as it can give a coarse description of their surroundings. Further, a full working CNN on a mobile device will help in reducing the workload on server side computation (as how currently networks run in the cloud) as now the forward pass of a neural net can compute image features on the user's device.

* **Computational speedups**

We aim to implement binary networks as described in [XNOR-Net](https://arxiv.org/abs/1603.05279). The key insight is that binary values occupy less memory than double/single-precision floating point values and hence if we use binary valued parameters and weights for the many layers and binary valued inputs, the memory footprint of the network will decrease. Further, operations like convolution can be implemented using binary operations that are faster than an _O(N^3)_ matrix multiplication. The authors of [XNOR-Net](https://arxiv.org/abs/1603.05279) claim that it is possible to compress networks like [AlexNet](https://papers.nips.cc/paper/4824-imagenet-classification-with-deep-convolutional-neural-networks.pdf) to 7.4MB size with a small loss in prediction accuracy. 

The implementation will therefore tap every possible source of speedup such as using fast matrix operation libraries like Armadillo, Accelerate framework, Eigen and very likely also tap the GPU using Metal in Objective-C. 
We will present some evidence as to what we actually choose in our final implementation when we present benchmarks for our project (please see the [Goals & Deliverables](.###Goals-&-Deliverables) section).

### The Challenge

The challenges involved in running a deep network on mobile device are two-fold, **memory** and **run-time**. As discussed in the [Background](.###Background) section, smaller memory footprint networks can actually run on the mobile device and faster operations involved in the forward pass at runtime can speedup the rate of processing input frames and running them at real time. 

We would like to note the following:

1. The key challenge here is to get the network running, not the accuracy of the network itself. This means that in our project, our main goal is to compress and run the network (even with just arbitrary values), and work on accuracy later.
2. Our project focuses on _running_ the network and *not training* on the mobile device. This means that for accurate object recognition, we will take pre-trained network weights and use them at test time in the device application, similar to what is demonstrated in the [TensorFlow iOS camera application](https://github.com/tensorflow/tensorflow/tree/master/tensorflow/contrib/ios_examples).
3. _Where do we get pre-trained weights for binary networks from?!_ : This is an interesting question because the authors of [XNOR-Net](https://arxiv.org/abs/1603.05279) highlight that they borrow network architectures from [AlexNet](https://papers.nips.cc/paper/4824-imagenet-classification-with-deep-convolutional-neural-networks.pdf) and [VGGNet](http://www.robots.ox.ac.uk/~vgg/research/very_deep/) and train the binary networks from scratch. This is our plan too, when we work on improving the accuracy of the network for object/scene recognition.

### Goals & Deliverables

* We _plan to achieve_ an implementation of a fully end-to-end binarized network framework for iOS that can run a network like [AlexNet](https://papers.nips.cc/paper/4824-imagenet-classification-with-deep-convolutional-neural-networks.pdf) on the device.
* We _hope to achieve_ the full deployment of an application for iOS with a compact model of pre-trained weights, capable of classifying objects and/or scenes that are captured by the camera.

**Evaluating our deliverables**

* We plan to present benchmarks for our framework as we implement and optimize it. The benchmarks will show the size of the pre-trained model that we compress using a binary network and the speed of the computation for a forward neural network pass for object recognition on a live video.

* A baseline is already provided to us by the [TensorFlow iOS camera application](https://github.com/tensorflow/tensorflow/tree/master/tensorflow/contrib/ios_examples) which uses a pre-trained [GoogleLeNet](http://static.googleusercontent.com/media/research.google.com/en//pubs/archive/43022.pdf) model (size approx. 50 MB) was able to perform object recognition on a video on our iPad Air 2 at 6.8 FPS. So one measure of success would be to beat this benchmark on the GoogleLeNet architecture.

![Realism in life](images/einstein_cartoon1-full-200x250.jpg)
([source](http://blogs.agu.org/wildwildscience/files/2009/09/einstein_cartoon1-full-336x420.jpg))

**"Let's be real folks, you have only 4 weeks!"**

_We believe_ we can achieve a working implementation of a forward pass on a compressed network model. We will regularly update this page with our progress and seek help when stuck. Since the main goal is to actually understand and implement the network framework in [XNOR-Net](https://arxiv.org/abs/1603.05279), most of our efforts will be in squeezing out every bit of optimization to run the network in real time on the device.



### Schedule

#### Task Breakdown

1. Profile the [TensorFlow iOS camera application](https://github.com/tensorflow/tensorflow/tree/master/tensorflow/contrib/ios_examples) (Both)
2. Build application carcass for development (Salvador)
3. Implement the atomic components required for a forward pass by an XNOR-Net. (Both)
4. Implement the fully running XNOR-Net based on VGGNet or AlexNet. (Both)
5. Build the profiling tasks for optimization. (Esha)
6. Optimize the slowest/most expensive components through CPU/GPU frameworks and libraries and algorithm tricks learnt in class. (Both)
7. Compare and analyze the implementation. (Salvador)
8. Improve application UI (controls, interface). (Esha)
9. Design and implement a real-use case scenario for the implemented net. (Both)
10. Make the demo video. (Both)

#### Hard Deadlines

1. Mid-project Checkpoint: 16 November, 2016
2. Project Demo: 8 December, 2016
3. Final Project Report: 11 December 2016

#### Calendar

| Date             | Description                    |
|------------------|:------------------------------:|
| 10 November 2016 | Fully implemented sub-modules  |
| 17 November 2016 | Fully implemented forward pass |
| 24 November 2016 | Benchmarks finalized           |
|  1 December 2016 | Application enhancement (UI)   |
|  7 December 2016 | Fully developed application    |


