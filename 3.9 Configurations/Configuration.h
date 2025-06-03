class Configuration{
    private:
        int num_rows;
        int num_cols;
        vector<Position*> arrayForest, arrayRiver, arrayFortification, arrayUrban, arraySpecialZone;
        Unit** liberationUnits;
        Unit** ARVNUnits;
        int eventCode;
        int libersize;
        int arvnsize;
    public:
        Configuration ( const string & filepath ):num_rows(0), num_cols(0), liberationUnits(nullptr), ARVNUnits(nullptr), libersize(0), arvnsize(0), eventCode(0){
            //if (){return;}
            ifstream file(filepath);
            if (!(file.is_open())){return;}
            string s;
            //cout<<"file is open"<<endl;
            while(getline(file,s)){
                //cout<<s<<endl;
                if (s.find("NUM_ROWS=")!=string::npos){
                    this->num_rows=stoi(s.substr(s.find("NUM_ROWS=")+9));
                }
                else if (s.find("NUM_COLS=")!=string::npos){
                    this->num_cols=stoi(s.substr(9+s.find("NUM_COLS=")));
                }
                else if (s.find("ARRAY_FOREST=")!=string::npos){
                    //this->arrayForest=stoi(s.substr(9));
                    parsePos(s.substr(13+s.find("ARRAY_FOREST=")),arrayForest);
                }
                else if (s.find("ARRAY_RIVER=")!=string::npos){
                    parsePos(s.substr(12+s.find("ARRAY_RIVER=")),arrayRiver);
                }
                else if (s.find("ARRAY_FORTIFICATION=")!=string::npos){
                    parsePos(s.substr(20+s.find("ARRAY_FORTIFICATION=")),arrayFortification);
                }
                else if (s.find("ARRAY_URBAN=")!=string::npos){
                    parsePos(s.substr(12+s.find("ARRAY_URBAN=")),arrayUrban);
                }
                else if (s.find("ARRAY_SPECIAL_ZONE=")!=string::npos){
                    parsePos(s.substr(19+s.find("ARRAY_SPECIAL_ZONE=")),arraySpecialZone);
                }
                else if (s.find("UNIT_LIST=")!=string::npos){
                    parseUnit(s.substr(10+s.find("UNIT_LIST=")));
                    //cout<<"done"<<endl;
                }
                else if (s.find("EVENT_CODE=")!=string::npos){
                    this->eventCode=stoi(s.substr(11+s.find("EVENT_CODE=")));
                    if (eventCode<0){eventCode=0;}
                    else if (eventCode>99){eventCode=eventCode%100;}
                }
            }
            file.close();
        }
        ~Configuration() {
            // Delete liberation units
            if (!arrayForest.empty())
            for (Position* pos : arrayForest){
                delete pos;
            }
            if (!arrayRiver.empty())
            for (Position* pos : arrayRiver){
                delete pos;
            }
            if (!arrayFortification.empty())
            for (Position* pos : arrayFortification){
                delete pos;
            }
            if (!arrayUrban.empty())
            for (Position* pos : arrayUrban){
                delete pos;
            }
            if (!arraySpecialZone.empty())
            for (Position* pos : arraySpecialZone){
                delete pos;
            }

            // if (liberationUnits){
            //     delete[] liberationUnits;
            //     liberationUnits=nullptr;
            // }

            // if (ARVNUnits){
            //     delete[] ARVNUnits;
            //     ARVNUnits=nullptr;
            // }
            if (liberationUnits) {
                for (int i = 0; i < libersize; ++i) {
                    delete liberationUnits[i];  // Delete each Unit*
                }
                delete[] liberationUnits;  // Delete the array itself
                liberationUnits = nullptr;
            }

            if (ARVNUnits) {
                for (int i = 0; i < arvnsize; ++i) {
                    delete ARVNUnits[i];  // Delete each Unit*
                }
                delete[] ARVNUnits;
                ARVNUnits = nullptr;
            }
            // for (Unit* unit : liberationUnits) {
            //     delete unit;
            // }
            // // Delete ARVN units
            // for (Unit* unit : ARVNUnits) {
            //     delete unit;
            // }
        }
        string str () const ;

        void parsePos(string s,vector<Position*> &arr);
        void parseUnit(string s);
        VehicleType stringToVehicleType(const string& name) {
            if (name == "TANK") return VehicleType::TANK;
            else if (name == "TRUCK") return VehicleType::TRUCK;
            else if (name == "ARTILLERY") return VehicleType::ARTILLERY;
            else if (name == "ANTIAIRCRAFT") return VehicleType::ANTIAIRCRAFT;
            else if (name == "ARMOREDCAR") return VehicleType::ARMOREDCAR;
            else if (name == "APC") return VehicleType::APC;
            else if (name == "MORTAR") return VehicleType::MORTAR;
            throw invalid_argument("Unknown infantry type");
            // ... other vehicle types
            //throw invalid_argument("Unknown vehicle type: " + name);
        }
        bool isVehicleType(const string& name) {
            return name == "TANK" || name == "TRUCK" || name == "MORTAR" ||
                   name == "ANTIAIRCRAFT" || name == "ARMOREDCAR" || 
                   name == "APC" || name == "ARTILLERY";
        }
        InfantryType stringToInfantryType(const string& name) {
            if (name == "SNIPER") return InfantryType::SNIPER;
            if (name == "ANTIAIRCRAFTSQUAD") return InfantryType::ANTIAIRCRAFTSQUAD;
            if (name == "MORTARSQUAD") return InfantryType::MORTARSQUAD;
            if (name == "ENGINEER") return InfantryType::ENGINEER;
            if (name == "SPECIALFORCES") return InfantryType::SPECIALFORCES;
            if (name == "REGULARINFANTRY") return InfantryType::REGULARINFANTRY;
            throw invalid_argument("Unknown infantry type");
        }
        bool isInfantryType(const string& name) {
            return name == "SNIPER" || name == "ANTIAIRCRAFTSQUAD" || 
                   name == "MORTARSQUAD" || name == "ENGINEER" ||
                   name == "SPECIALFORCES" || name == "REGULARINFANTRY";
        }
        int getrows(){return this->num_rows;}
        int getcols(){return this->num_cols;}
        vector<Position*> getarrayForest();
        vector<Position*> getarrayRiver();
        vector<Position*> getarrayFortification();
        vector<Position*> getarrayUrban();
        vector<Position*> getarraySpecialZone();
        Unit** getliberationunits();
        Unit** getarvnunits();
        int geteventcode();
        int getlibersize(){return libersize;}
        int getarvnsize(){return arvnsize;}
};
