void Configuration::parsePos(string s,vector<Position*> &arr){
    int start=s.find("[");
    int end=s.find("]");
    if (start==string::npos || end==string::npos || (end-1) <=start){return;}
    //stringstream ss;
    int index=s.find(")");
    //start+=1;
    string pos;
    while(index!=string::npos){
        int open=s.find("(");
        pos=s.substr(open,index-open+1);
        Position* position=new Position(pos);
        arr.push_back(position);
        s=s.substr(index+1);
        index=s.find(")");
    }
}
void Configuration::parseUnit(string s){
    //cout<<"testtttt:"<<s<<endl;
    int start=s.find("[");
    int open=s.find("(",start);
    //cout<<"confi:working here"<<endl;
    if (s.find("[]") != string::npos || s.find("[ ]") != string::npos) {
        liberationUnits = nullptr;
        ARVNUnits = nullptr;
        libersize = 0;
        arvnsize = 0;
        //cout<<"confi:working here"<<endl;
        return;
    }
    int index;
    string unitname;
    string para;
    //const Position pos;
    int quantity;
    int weight;
    int isARVN;
    int r,c;
    //VehicleType b;
    vector<Unit*> templiber;
    vector<Unit*> temparvn;
    while (open!=string::npos){
        unitname=s.substr(start+1,open-start-1);
        index=s.find(")",start);
        index=s.find(")",index+1);
        para=s.substr(open,index-open+1);
        //cout<<"para:"<<para<<endl;
        // if (static_cast<VehicleType>(unitname)){
            
        // }
        //for (int i=0;i<VehicleType.length())
        stringstream ss(para);
        char ignore;
        ss>>ignore>>quantity>>ignore>>weight>>ignore;
        ss>>ignore>>r>>ignore>>c>>ignore>>ignore>>isARVN;
        //cout<<quantity<<" "<<weight<<" "<<r<<" "<<c<<" "<<isARVN<<endl;
        const Position pos(r,c);
        // if (isVehicleType(unitname)){
        //     Unit* unit=new Vehicle(quantity,weight,pos,stringToVehicleType(unitname));
        //     //ARVNUnits.push_back(unit);
        // }
        // else if (isInfantryType(unitname)){
        //     Unit* unit=new Infantry(quantity,weight,pos,stringToInfantryType(unitname));
        //     //liberationUnits.push_back(unit);
        // }
        Unit* unit = nullptr;
        if (isVehicleType(unitname)){
            unit=new Vehicle(quantity,weight,pos,stringToVehicleType(unitname));
            // ARVNUnits.push_back(unit);
        }
        else if (isInfantryType(unitname)){
            unit=new Infantry(quantity,weight,pos,stringToInfantryType(unitname));
            // liberationUnits.push_back(unit);
        }
        //cout<<isARVN<<endl;
        if (isARVN){
            temparvn.push_back(unit);
        }
        else{
            templiber.push_back(unit);
        }
        //cout<<"unit:"<<unit<<endl;
        start=s.find(",",index);
        open=s.find("(",start);
        // open=para.find("(");
        // const Position pos=Position(s.substr(open,index-open+1));
        // //arr=new Vehicle(start,open,a,unitname);
        // open=s.find(",",index);
        // isARVN = stoi(s.substr(open+1,1));

        // start=s.find(",",open+1);
        // open=s.find("(",start);
    }
    liberationUnits=nullptr;
    if (templiber.size()>0){
        liberationUnits=new Unit*[templiber.size()];
        for (int i=0;i<templiber.size();i++){
            liberationUnits[i]=templiber[i];
        }
    }
    this->libersize=templiber.size();
    ARVNUnits=nullptr;
    if (temparvn.size()>0){
        ARVNUnits=new Unit*[temparvn.size()];
        for (int i=0;i<temparvn.size();i++){
            ARVNUnits[i]=temparvn[i];
        }
    }
    this->arvnsize=temparvn.size();
    // for (Unit* u:templiber){
    //     cout<<u->str()<<endl;
    // }
    // for (Unit* u:temparvn){
    //     cout<<u->str()<<endl;
    // }
    templiber.clear();
    temparvn.clear();
}
string Configuration::str() const{
    stringstream ss;
    //c="Vehicle[vehicleType="+vehicleType+",quantity="+quantity+",weight="+weight+",pos="+pos;
    ss<<"[num_rows="<<num_rows<<",num_cols="<<num_cols;//",arrayForest="<<arrayForest<<",pos=" << "(" << pos.getRow() << "," << pos.getCol() << ")" << "]";
    ss<<",arrayForest=[";
    for (size_t i=0;i<arrayForest.size();i++){
        ss<<arrayForest[i]->str();
        if (i!=arrayForest.size()-1){ss<<",";}
    }
    ss<<"]";

    ss<<",arrayRiver=[";
    for (size_t i=0;i<arrayRiver.size();i++){
        ss<<arrayRiver[i]->str();
        //cout<<"\ntest:"<<arrayRiver[i]->str()<<"\n";
        if (i!=arrayRiver.size()-1){ss<<",";}
    }
    ss<<"]";

    ss<<",arrayFortification=[";
    for (size_t i=0;i<arrayFortification.size();i++){
        ss<<arrayFortification[i]->str();
        if (i!=arrayFortification.size()-1){ss<<",";}
    }
    ss<<"]";

    ss<<",arrayUrban=[";
    for (size_t i=0;i<arrayUrban.size();i++){
        ss<<arrayUrban[i]->str();
        if (i!=arrayUrban.size()-1){ss<<",";}
    }
    ss<<"]";

    ss<<",arraySpecialZone=[";
    for (size_t i=0;i<arraySpecialZone.size();i++){
        ss<<arraySpecialZone[i]->str();
        if (i!=arraySpecialZone.size()-1){ss<<",";}
    }
    ss<<"]";

    ss<<",liberationUnits=[";
    for (int i=0;i<libersize;i++){
        ss<<liberationUnits[i]->str();
        if (i!=libersize-1){ss<<",";}
    }
    ss<<"]";

    ss<<",ARVNUnits=[";
    for (size_t i=0;i<arvnsize;i++){
        ss<<ARVNUnits[i]->str();
        if (i!=arvnsize-1){ss<<",";}
    }
    ss<<"]";

    ss<<",eventCode="<<eventCode<<"]";
    // ss<<",arraySpecialZone=[";
    // for (size_t i=0;i<arraySpecialZone.size();i++){
    //     ss<<arraySpecialZone[i]->str();
    //     if (i!=arraySpecialZone.size()-1){ss<<",";}
    // }
    // ss<<"]";
    return ss.str();
}
