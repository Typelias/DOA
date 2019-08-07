Linear = load("Linear Search.txt");
Binary = load("Binary Search.txt");
Tree = load("Binary Search Tree.txt");
Table = load("Hashtable.txt");

figure(1);
hold on
plot(Linear(:,1),Linear(:,2),'-r');
errorbar(Linear(:,1),Linear(:,2),Linear(:,2)-(Linear(:,3)/2),Linear(:,2)+(Linear(:,3)/2),'.r');

plot(Binary(:,1),Binary(:,2),'-b');
errorbar(Binary(:,1),Binary(:,2),Binary(:,2)-(Binary(:,3)/2),Binary(:,2)+(Binary(:,3)/2),'.b');

plot(Tree(:,1),Tree(:,2),'-y');
errorbar(Tree(:,1),Tree(:,2),Tree(:,2)-(Tree(:,3)/2),Tree(:,2)+(Tree(:,3)/2),'.y');

plot(Table(:,1),Table(:,2),'-k');
errorbar(Table(:,1),Table(:,2),Table(:,2)-(Table(:,3)/2),Table(:,2)+(Table(:,3)/2),'.k');
legend({'Linear Search','Linear Search stdev','Binary Search','Binary Search stdev','Binary Search Tree','Binary Search Tree stdev','Hashtable','Hashtable stdev'});
hold off;

figure(2)
hold on
plot(Binary(:,1),Binary(:,2),'-b');
errorbar(Binary(:,1),Binary(:,2),Binary(:,2)-(Binary(:,3)/2),Binary(:,2)+(Binary(:,3)/2),'.b');
plot(Table(:,1),Table(:,2),'-k');
errorbar(Table(:,1),Table(:,2),Table(:,2)-(Table(:,3)/2),Table(:,2)+(Table(:,3)/2),'.k');
plot(Tree(:,1),Tree(:,2),'-y');
errorbar(Tree(:,1),Tree(:,2),Tree(:,2)-(Tree(:,3)/2),Tree(:,2)+(Tree(:,3)/2),'.y');
legend({'Binary Search','Binary Search stdev','Hashtable','Hashtable stdev','Binary Search Tree','Binary Search Tree stdev'});
hold off

