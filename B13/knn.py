import csv
from math import sqrt
import random
import operator


#testData=[] and not just testData
def loadDataset(filename,split,trainingData=[],testData=[]):
    with open(filename,'r') as csvfile:
        line = csv.reader(csvfile)
        dataset=list(line)
        for x in range(len(dataset)-1):
            #COnvert to float please
            for y in range(4):
                dataset[x][y] = float(dataset[x][y])
            if(random.random()<split):
                trainingData.append(dataset[x])
            else:
                testData.append(dataset[x])
def EuclideanDistance(instance1,instance2,length):
    value=0
    for x in range(length):
        value=value+pow((instance1[x]-instance2[x]), 2)
    return sqrt(value)
def nearestNeighbour(trainingData,instance,k):
    distance=[]
    for x in range(len(trainingData)):
        dist=EuclideanDistance(instance, trainingData[x], len(instance)-1)
        distance.append((trainingData[x],dist))
    distance.sort(key=operator.itemgetter(1))
    neighbours=[]
    for x in range(k):
        neighbours.append(distance[x][0])
    return neighbours
def getResponse(neighbours):
    classvotes={}
    for x in range(len(neighbours)):
        temp=neighbours[x][-1]
        if temp in classvotes:
            classvotes[temp]+=1
        else:
            classvotes[temp]=1
    sortedVotes=sorted(classvotes.items(),key= operator.itemgetter(1), reverse=True)
    return sortedVotes[0][0]
def getAccuracy(testData,predictions):
    correct=0
    for x in range(len(testData)):
        if(testData[x][-1]==predictions[x]):
            correct+=1
    accuracy = float(correct/float(len(testData)))*100
    return accuracy
    
def main():
    # prepare data
    trainingSet=[]
    testSet=[]
    split = 0.7
    loadDataset('iris.data', split, trainingSet, testSet)
    print ('Train set: ') 
    print(len(trainingSet))
    print ('Test set: ' + repr(len(testSet)))
    # generate predictions
    predictions=[]
    k = 3
    for x in range(len(testSet)):
        neighbors = nearestNeighbour(trainingSet, testSet[x], k)
        result = getResponse(neighbors)
        predictions.append(result)
        print('> predicted=' + repr(result) + ', actual=' + repr(testSet[x][-1]))
    accuracy = getAccuracy(testSet, predictions)
    print('Accuracy: ' + repr(accuracy) + '%')
    
main()