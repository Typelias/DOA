Standard = load("[Random]std::sort.txt");
MedianOfThree = load("[Random]Median Quicksort.txt");
Insertion = load("[Random]Inserton Sort.txt");
Selection = load("[Random]Selection Sort.txt");
Quick = load("[Random]Quicksort.txt");

figure(1);
hold on
plot(Standard(:,1),Standard(:,2),'-r');
errorbar(Standard(:,1),Standard(:,2),Standard(:,2)-(Standard(:,3)/2),Standard(:,2)+(Standard(:,3)/2),'.r');

plot(MedianOfThree(:,1),MedianOfThree(:,2),'-b');
errorbar(MedianOfThree(:,1),MedianOfThree(:,2),MedianOfThree(:,2)-(MedianOfThree(:,3)/2),MedianOfThree(:,2)+(MedianOfThree(:,3)/2),'.b');

plot(Insertion(:,1),Insertion(:,2),'-y');
errorbar(Insertion(:,1),Insertion(:,2),Insertion(:,2)-(Insertion(:,3)/2),Insertion(:,2)+(Insertion(:,3)/2),'.y');

plot(Quick(:,1),Quick(:,2),'-k');
errorbar(Quick(:,1),Quick(:,2),Quick(:,2)-(Quick(:,3)/2),Quick(:,2)+(Quick(:,3)/2),'.k');

plot(Selection(:,1),Selection(:,2),'-g');
errorbar(Selection(:,1),Selection(:,2),Selection(:,2)-(Selection(:,3)/2),Selection(:,2)+(Selection(:,3)/2),'.g');
legend({'std::sort','std::sort stdev','Median of Three','Median of Three stdev','Insertion Sort','Insertion Sort stdev','Quicksort','Quicksort stdev','Selection Sort','Selection Sort stdev'});
hold off

figure(2);
hold on
plot(Standard(:,1),Standard(:,2),'-r');
errorbar(Standard(:,1),Standard(:,2),Standard(:,2)-(Standard(:,3)/2),Standard(:,2)+(Standard(:,3)/2),'.r');

plot(MedianOfThree(:,1),MedianOfThree(:,2),'-b');
errorbar(MedianOfThree(:,1),MedianOfThree(:,2),MedianOfThree(:,2)-(MedianOfThree(:,3)/2),MedianOfThree(:,2)+(MedianOfThree(:,3)/2),'.b');

plot(Quick(:,1),Quick(:,2),'-k');
errorbar(Quick(:,1),Quick(:,2),Quick(:,2)-(Quick(:,3)/2),Quick(:,2)+(Quick(:,3)/2),'.k');
legend({'std::sort','std::sort stdev','Median of Three','Median of Three stdev','Quicksort','Quicksort stdev'});
hold off
