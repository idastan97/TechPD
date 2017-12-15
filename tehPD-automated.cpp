#include <iostream>
#include <vector>
using namespace std;

typedef struct {
	string stan;
    int qty;
    double tarif;
    double nds;
    double total;
} station;

double toDub(string s){
	double res=0;
	int drob=1;
	bool dotFound=0;
	for (int i=0; i<s.length(); i++){
		if (s[i]<='9' && s[i]>='0'){
			res=res*10+s[i]-'0';
			if (dotFound){
				drob=drob*10;
			}
		} else if (s[i]==','){
			dotFound=1;
		}
	}
	if (s[s.length()-1]=='-'){
		return -res/drob;
	} else {
		return res/drob;
	}
}

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	string s;
	vector<station> stations;
	int decade=0;
	
    int qtyDecadeTotal=0;
    double tarifDecadeTotal=0;
    double ndsDecadeTotal=0;
    double totalDecadeTotal=0;
    
    int qtyTotal=0;
    double tarifTotal=0;
    double ndsTotal=0;
    double totalTotal=0;
    cout<<"Станция;Кол-во;Тариф;НДС;Всего";
	while (cin>>s){
		if (s=="Перечень"){
			string tmp, perId, perDate;
			cin>>tmp>>perId>>tmp>>perDate;
			int day=(perDate[0]-'0')*10+perDate[1]-'0';
			int newDecade;
			if (day<=10){
				newDecade=0;
			} else if (day<=20){
				newDecade=1;
			} else {
				newDecade=2;
			}
			if (newDecade!=decade){
				cout<<"\nИтог\n";
				while (stations.size()>0){
					cout<<stations.back().stan<<";";
					printf("%i;%.2f;%.2f;%.2f\n", stations.back().qty, stations.back().tarif, stations.back().nds, stations.back().total);
					stations.pop_back();
				}
				cout<<" ;";
				printf("%i;%.2f;%.2f;%.2f\n", qtyDecadeTotal, tarifDecadeTotal, ndsDecadeTotal, totalDecadeTotal);
				qtyDecadeTotal=0;
			    tarifDecadeTotal=0;
			    ndsDecadeTotal=0;
			    totalDecadeTotal=0;
			    
			    decade=newDecade;
			    
				cout<<endl<<endl<<"Станция;Кол-во;Тариф;НДС;Всего";
			}
			cout<<"\nПеречень № "<<perId<<" от "<<perDate<<" г."<<endl;
		}
		if (s=="Станция") {
			string id, name, temp="";
			cin>>id;
			getline(cin, name);
			string stan=id+name;
			int index=-1;
			for (int i=0; i<stations.size(); i++){
				if (stations[i].stan==stan){
					index=i;
					break;
				}
			}
			if (index<0){
				index=stations.size();
				station newStation = {stan, 0, 0, 0, 0};
				stations.push_back(newStation);
			}
			while (1){
				cin>>temp;
				if (temp=="по"){
					cin>>temp;
					if (temp=="станции:"){
						int qty;
						string tarifS, ndsS, totalS;
						cin>>temp>>temp>>qty>>temp>>temp>>tarifS>>temp>>temp>>temp>>temp>>ndsS>>temp>>totalS;
						double tarif=toDub(tarifS), nds=toDub(ndsS), total=toDub(totalS);
						cout<<stan<<";"<<qty<<";";
						printf("%.2f;%.2f;%.2f\n", tarif, nds, total);
						
						stations[index].qty+=qty;
						stations[index].tarif+=tarif;
						stations[index].nds+=nds;
						stations[index].total+=total;
						
						qtyTotal+=qty;
					    tarifTotal+=tarif;
					    ndsTotal+=nds;
					    totalTotal+=total;
					    
					    qtyDecadeTotal+=qty;
					    tarifDecadeTotal+=tarif;
					    ndsDecadeTotal+=nds;
					    totalDecadeTotal+=total;
					    break;
					}
				}
			}
		}
	}
	cout<<"\nИтог\n";
	while (stations.size()>0){
		cout<<stations.back().stan<<";";
		printf("%i;%.2f;%.2f;%.2f\n", stations.back().qty, stations.back().tarif, stations.back().nds, stations.back().total);
		stations.pop_back();
	}
	cout<<" ;";
	printf("%i;%.2f;%.2f;%.2f\n", qtyDecadeTotal, tarifDecadeTotal, ndsDecadeTotal, totalDecadeTotal);
	qtyDecadeTotal=0;
	tarifDecadeTotal=0;
	ndsDecadeTotal=0;
	totalDecadeTotal=0;
	cout<<endl<<endl;
	
	cout<<" ;";
	printf("%i;%.2f;%.2f;%.2f\n", qtyTotal, tarifTotal, ndsTotal, totalTotal);
	return 0;
}
