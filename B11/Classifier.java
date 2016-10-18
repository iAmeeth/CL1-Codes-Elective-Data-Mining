import java.io.BufferedReader;
import java.io.FileReader;

import weka.classifiers.Evaluation;
import weka.classifiers.bayes.NaiveBayes;
import weka.classifiers.trees.J48;
import weka.core.Debug.Random;
import weka.core.Instances;

public class Classifier 
{
		public void NaiveBayes() throws Exception
		{
		System.out.println("\n\n****************************************************************\n");
		BufferedReader br = new BufferedReader(new FileReader("src/test.arff"));
		Instances train = new Instances(br);
		train.setClassIndex(train.numAttributes()-1);
		NaiveBayes nb = new NaiveBayes();	
		nb.buildClassifier(train);
		
		Evaluation eval = new Evaluation(train);
		eval.crossValidateModel(nb, train, 10,new Random(1));
		
		System.out.print(eval.toSummaryString());
		System.out.print(eval.toClassDetailsString());
		System.out.print(eval.confusionMatrix());
		System.out.println("\n\n****************************************************************\n");
		}
		public void DecisionTree() throws Exception
		{
			System.out.println("\n\n****************************************************************\n");
			BufferedReader bre = new BufferedReader(new FileReader("src/test.arff"));
			Instances train = new Instances(bre);
			train.setClassIndex(train.numAttributes()-1);
			J48 decision = new J48();
			decision.setOptions(null);
			decision.buildClassifier(train);
			Evaluation eval = new Evaluation(train);
			eval.evaluateModel(decision, train);
			System.out.println("\n\n***************************1*************************************\n");
			System.out.print(eval.toSummaryString());
			System.out.println("\n\n****************************2************************************\n");
			bre = new BufferedReader(new FileReader("src/test.arff"));
			Instances test = new Instances(bre);
			test.setClassIndex(train.numAttributes()-1);
			eval.evaluateModel(decision, test);
			System.out.print(eval.toSummaryString());
			
			System.out.println("\n\n****************************************************************\n");
			System.out.print(eval.toClassDetailsString());
			System.out.print(eval.toMatrixString());
			System.out.println("\n\n****************************************************************\n");
		    
		}
	public static void main(String[] args) throws Exception
	{
		// TODO Auto-generated method stub
		Classifier c = new Classifier();
		c.DecisionTree();
		c.NaiveBayes();
		
	}

}
