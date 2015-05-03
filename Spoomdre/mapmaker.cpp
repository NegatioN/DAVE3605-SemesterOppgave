#include "mapmaker.hpp"
#include "abstract_sector_factory.hpp"
#include "normal_sector_factory.hpp"

std::vector<sector*> mapmaker::createMap(){
	int id = 1;
	std::vector<sector*> sectors;

	AbstractSectorFactory* factory = new NormalSectorFactory();
	
	// vertexes for test-map
	vertex v1 = vertex{50, 50};
	vertex v2 = vertex{90, 50};
	vertex v3 = vertex{120, 75};
	vertex v4 = vertex{120, 100};
	vertex v5 = vertex{50, 100};

	vertex v6 = vertex{90, 10};
	vertex v7 = vertex{50, 10};

	vertex v8= vertex{120, 10};

	vertex v9 = vertex{150, 10};
	vertex v10= vertex{150, 75};

	vertex v11= vertex{40, 120};

	vertex v12 = vertex{10, 10};
	vertex v13 = vertex{10, 50};
	vertex v14 = vertex{50, 20};
	vertex v15 = vertex{50, 30};
	vertex v16 = vertex{40, 50};
	vertex v17 = vertex{40, 30};
	vertex v18 = vertex{40, 20};
	vertex v19 = vertex{40, 10};

	vertex v20 = vertex{0, 50};
	vertex v21 = vertex{0, 10};

	std::vector<vertex> s1_vertex;
	std::vector<vertex> s2_vertex;
	std::vector<vertex> s3_vertex;
	std::vector<vertex> s4_vertex;
	std::vector<vertex> s5_vertex;
	std::vector<vertex> s6_vertex;
	std::vector<vertex> s7_vertex;

	s1_vertex.push_back(v1);
	s1_vertex.push_back(v2);
	s1_vertex.push_back(v3);
	s1_vertex.push_back(v4);
	s1_vertex.push_back(v5);

	s2_vertex.push_back(v1);
	s2_vertex.push_back(v15);
	s2_vertex.push_back(v14);
	s2_vertex.push_back(v7);
	s2_vertex.push_back(v6);
	s2_vertex.push_back(v2);

	s3_vertex.push_back(v2);
	s3_vertex.push_back(v6);
	s3_vertex.push_back(v8);
	s3_vertex.push_back(v3);

	s4_vertex.push_back(v8);
	s4_vertex.push_back(v9);
	s4_vertex.push_back(v10);
	s4_vertex.push_back(v3);

	s6_vertex.push_back(v15);
	s6_vertex.push_back(v17);
	s6_vertex.push_back(v18);
	s6_vertex.push_back(v14);

	s5_vertex.push_back(v17);
	s5_vertex.push_back(v16);
	s5_vertex.push_back(v13);
	s5_vertex.push_back(v12);
	s5_vertex.push_back(v19);
	s5_vertex.push_back(v18);

	s7_vertex.push_back(v13);
	s7_vertex.push_back(v20);
	s7_vertex.push_back(v21);
	s7_vertex.push_back(v12);

	sector* s1 = factory->createSector(id++, 10.f, 40.f, s1_vertex);
	sector* s2 = factory->createSector(id++, 25.f, 45.f, s2_vertex);
	sector* s3 = factory->createSector(id++,  7.f, 35.f, s3_vertex);
	sector* s4 = factory->createSector(id++, 10.f, 30.f, s4_vertex);
	sector* s5 = factory->createSector(id++, 25.f, 45.f, s5_vertex);
	sector* s6 = factory->createSector(id++, 25.f, 45.f, s6_vertex);
	sector* s7 = factory->createSector(id++, 25.f, 45.f, s7_vertex);

	static LevelPortal lvlPortal{5, 30, 1, 2};
	s7->setLevelPortal(&lvlPortal);

	s1->addNeighbour(s2);
	s1->addNeighbour(s3);
	s2->addNeighbour(s1);
	s2->addNeighbour(s3);
	s2->addNeighbour(s6);
	s3->addNeighbour(s1);
	s3->addNeighbour(s2);
	s3->addNeighbour(s4);
	s4->addNeighbour(s3);
	s5->addNeighbour(s6);
	s5->addNeighbour(s7);
	s6->addNeighbour(s2);
	s6->addNeighbour(s5);
	s7->addNeighbour(s5);

	static door d1{v14, v15, true}; // "smallest" point first

	s2->addDoor(&d1);
	s6->addDoor(&d1);

	sectors.push_back(s1);
	sectors.push_back(s2);
	sectors.push_back(s3);
	sectors.push_back(s4);
	sectors.push_back(s6);
	sectors.push_back(s5);
	sectors.push_back(s7);

	return sectors;
}

std::vector<sector*> mapmaker::createShowcaseMap(){
	int id = 1;
	std::vector<sector*> sectors;

	AbstractSectorFactory* factory = new NormalSectorFactory();
	

	vertex v1 = vertex{0, 0};
	vertex v2 = vertex{10, 0};
	vertex v3 = vertex{10, 30};
	vertex v4 = vertex{0, 30};

	vertex v5 = vertex{30, 0};
	vertex v6 = vertex{40, 0};
	vertex v7 = vertex{40, 30};
	vertex v8 = vertex{30, 30};
	
	vertex v9 = vertex{30, 10};
	vertex v10 = vertex{10, 10};

	vertex v11 = vertex{30, 20};
	vertex v12 = vertex{10, 20};

	vertex v13 = vertex{10, 40};
	vertex v14 = vertex{30, 40};

	vertex v15 = vertex{10, 60};
	vertex v16 = vertex{30, 60};
	vertex v17 = vertex{10, 70};
	vertex v18 = vertex{30, 70};

	vertex v19 = vertex{0, 80};
	vertex v20 = vertex{10, 80};
	vertex v21 = vertex{30, 80};
	vertex v22 = vertex{40, 80};

	vertex v23 = vertex{10, 120};
	vertex v24 = vertex{30, 120};
	vertex v25 = vertex{0, 130};
	vertex v26 = vertex{10, 130};
	vertex v27 = vertex{20, 130};
	vertex v28 = vertex{30, 130};
	vertex v29 = vertex{40, 130};
	vertex v30 = vertex{20, 150};
	vertex v31 = vertex{10, 160};
	vertex v32 = vertex{20, 160};

	vertex v33 = vertex{90, 130};
	vertex v34 = vertex{60, 140};
	vertex v35 = vertex{70, 140};
	vertex v36 = vertex{60, 160};
	vertex v37 = vertex{70, 170};
	vertex v38 = vertex{90, 170};
	vertex v39 = vertex{70, 180};
	vertex v40 = vertex{90, 180};
	vertex v41 = vertex{60, 150};
	vertex v42 = vertex{60, 130};
	vertex v43 = vertex{70, 130};
	vertex v44 = vertex{50, 150};
	vertex v45 = vertex{50, 130};

	vertex v46 = vertex{100, 180};
	vertex v47 = vertex{120, 180};
	vertex v48 = vertex{100, 170};
	vertex v49 = vertex{100, 110};
	vertex v50 = vertex{100, 100};
	vertex v51 = vertex{120, 100};

	vertex v52 = vertex{90, 110};
	vertex v53 = vertex{90, 100};
	vertex v54 = vertex{50, 120};
	vertex v55 = vertex{90, 120};
	vertex v56 = vertex{50, 70};
	vertex v57 = vertex{90, 70};
	vertex v58 = vertex{90, 80};
	vertex v59 = vertex{90, 90};
	vertex v60 = vertex{100, 80};
	vertex v61 = vertex{100, 90};

	vertex v62 = vertex{120, 90};
	vertex v63 = vertex{100, 60};
	vertex v64 = vertex{100, 50};
	vertex v65 = vertex{120, 50};

	vertex v66 = vertex{50, 60};
	vertex v67 = vertex{50, 50};
	vertex v68 = vertex{60, 50};
	vertex v69 = vertex{50, 40};
	vertex v70 = vertex{60, 40};

	vertex v71 = vertex{100, 40};
	vertex v72 = vertex{50, 0};
	vertex v73 = vertex{100, 0};
	vertex v74 = vertex{100, 20};
	vertex v75 = vertex{100, 30};

	vertex v76 = vertex{120, 20};
	vertex v77 = vertex{120, 30};
	vertex v78 = vertex{120, 10};
	vertex v79 = vertex{140, 10};
	vertex v80 = vertex{120, 40};
	vertex v81 = vertex{140, 40};


	std::vector<vertex> s1_vertex;
	std::vector<vertex> s2_vertex;
	std::vector<vertex> s3_vertex;
	std::vector<vertex> s4_vertex;
	std::vector<vertex> s5_vertex;
	std::vector<vertex> s6_vertex;
	std::vector<vertex> s7_vertex;
	std::vector<vertex> s8_vertex;
	std::vector<vertex> s9_vertex;
	std::vector<vertex> s10_vertex;
	std::vector<vertex> s11_vertex;
	std::vector<vertex> s12_vertex;
	std::vector<vertex> s13_vertex;
	std::vector<vertex> s14_vertex;
	std::vector<vertex> s15_vertex;
	std::vector<vertex> s16_vertex;
	std::vector<vertex> s17_vertex;
	std::vector<vertex> s18_vertex;
	std::vector<vertex> s19_vertex;
	std::vector<vertex> s20_vertex;
	std::vector<vertex> s21_vertex;
	std::vector<vertex> s22_vertex;
	std::vector<vertex> s23_vertex;
	std::vector<vertex> s24_vertex;
	std::vector<vertex> s25_vertex;
	std::vector<vertex> s26_vertex;
	std::vector<vertex> s27_vertex;
	std::vector<vertex> s28_vertex;
	std::vector<vertex> s29_vertex;
	std::vector<vertex> s30_vertex;


	// FIRST-ROOM STAIRS 1ST SIDE
	s1_vertex.push_back(v1);
	s1_vertex.push_back(v2);
	s1_vertex.push_back(v10);
	s1_vertex.push_back(v12);
	s1_vertex.push_back(v3);
	s1_vertex.push_back(v4);

	// FIRST-ROOM STAIRS 2ND SIDE
	s2_vertex.push_back(v5);
	s2_vertex.push_back(v6);
	s2_vertex.push_back(v7);
	s2_vertex.push_back(v8);
	s2_vertex.push_back(v11);
	s2_vertex.push_back(v9);

	// FIRST-ROOM STAIRS FRONT
	s3_vertex.push_back(v2);
	s3_vertex.push_back(v5);
	s3_vertex.push_back(v9);
	s3_vertex.push_back(v10);

	// FIRST-ROOM STAIRS STAIR-1
	s4_vertex.push_back(v10);
	s4_vertex.push_back(v9);
	s4_vertex.push_back(v11);
	s4_vertex.push_back(v12);

	// FIRST-ROOM STAIRS STAIR-2
	s5_vertex.push_back(v12);
	s5_vertex.push_back(v11);
	s5_vertex.push_back(v8);
	s5_vertex.push_back(v3);

	// FIRST-ROOM BOTTOM-BRIDGE
	s6_vertex.push_back(v3);
	s6_vertex.push_back(v8);
	s6_vertex.push_back(v14);
	s6_vertex.push_back(v13);

	// FIRST-ROOM SIDE-1-BRIDGE
	s7_vertex.push_back(v4);
	s7_vertex.push_back(v3);
	s7_vertex.push_back(v13);
	s7_vertex.push_back(v15);
	s7_vertex.push_back(v17);
	s7_vertex.push_back(v20);
	s7_vertex.push_back(v19);

	// FIRST-ROOM SIDE-2-BRIDGE
	s8_vertex.push_back(v8);
	s8_vertex.push_back(v7);
	s8_vertex.push_back(v22);
	s8_vertex.push_back(v21);
	s8_vertex.push_back(v18);
	s8_vertex.push_back(v16);
	s8_vertex.push_back(v14);

	// FIRST-ROOM TOP-BRIDGE
	s9_vertex.push_back(v17);
	s9_vertex.push_back(v18);
	s9_vertex.push_back(v21);
	s9_vertex.push_back(v20);

	// FIRST-ROOM PIT
	s10_vertex.push_back(v13);
	s10_vertex.push_back(v14);
	s10_vertex.push_back(v16);
	s10_vertex.push_back(v15);

	// FIRST-ROOM PIT-STAIR
	s11_vertex.push_back(v15);
	s11_vertex.push_back(v16);
	s11_vertex.push_back(v18);
	s11_vertex.push_back(v17);

	// HALLWAY-1 FROM FIRST-ROOM
	s12_vertex.push_back(v19);
	s12_vertex.push_back(v20);
	s12_vertex.push_back(v23);
	s12_vertex.push_back(v26);
	s12_vertex.push_back(v25);

	// HALLWAY-2 FROM FIRST-ROOM
	s13_vertex.push_back(v21);
	s13_vertex.push_back(v22);
	s13_vertex.push_back(v29);
	s13_vertex.push_back(v28);
	s13_vertex.push_back(v24);

	// HALLWAY-CROSS-SECTION FROM FIRST-ROOM
	s14_vertex.push_back(v23);
	s14_vertex.push_back(v24);
	s14_vertex.push_back(v28);
	s14_vertex.push_back(v27);
	s14_vertex.push_back(v26);

	// HALLWAY-3 FROM FIRST-ROOM
	s15_vertex.push_back(v26);
	s15_vertex.push_back(v27);
	s15_vertex.push_back(v30);
	s15_vertex.push_back(v32);
	s15_vertex.push_back(v31);

	// HALLWAY-4
	s16_vertex.push_back(v30);
	s16_vertex.push_back(v44);
	s16_vertex.push_back(v41);
	s16_vertex.push_back(v36);
	s16_vertex.push_back(v32);

	// HALLWAY-5
	s17_vertex.push_back(v45);
	s17_vertex.push_back(v42);
	s17_vertex.push_back(v34);
	s17_vertex.push_back(v41);
	s17_vertex.push_back(v44);

	// HALLWAY-6
	s18_vertex.push_back(v42);
	s18_vertex.push_back(v43);
	s18_vertex.push_back(v35);
	s18_vertex.push_back(v34);

	// HALLWAY-7
	s19_vertex.push_back(v43);
	s19_vertex.push_back(v33);
	s19_vertex.push_back(v38);
	s19_vertex.push_back(v40);
	s19_vertex.push_back(v39);
	s19_vertex.push_back(v35);

	// HALLWAY-8
	s20_vertex.push_back(v38);
	s20_vertex.push_back(v48);
	s20_vertex.push_back(v46);
	s20_vertex.push_back(v40);

	// HALLWAY-9
	s21_vertex.push_back(v50);
	s21_vertex.push_back(v51);
	s21_vertex.push_back(v47);
	s21_vertex.push_back(v46);
	s21_vertex.push_back(v48);
	s21_vertex.push_back(v49);

	// HALLWAY-10
	s22_vertex.push_back(v53);
	s22_vertex.push_back(v50);
	s22_vertex.push_back(v49);
	s22_vertex.push_back(v52);

	// ROOM-2
	s23_vertex.push_back(v56);
	s23_vertex.push_back(v57);
	s23_vertex.push_back(v58);
	s23_vertex.push_back(v59);
	s23_vertex.push_back(v53);
	s23_vertex.push_back(v52);
	s23_vertex.push_back(v55);
	s23_vertex.push_back(v54);
	
	// HALLWAY-1 FROM ROOM-2
	s24_vertex.push_back(v58);
	s24_vertex.push_back(v60);
	s24_vertex.push_back(v61);
	s24_vertex.push_back(v59);

	// HALLWAY-2 FROM ROOM-2
	s25_vertex.push_back(v64);
	s25_vertex.push_back(v65);
	s25_vertex.push_back(v62);
	s25_vertex.push_back(v61);
	s25_vertex.push_back(v60);
	s25_vertex.push_back(v63);

	// HALLWAY-3 FROM ROOM-2
	s26_vertex.push_back(v67);
	s26_vertex.push_back(v68);
	s26_vertex.push_back(v64);
	s26_vertex.push_back(v63);
	s26_vertex.push_back(v66);

	// HALLWAY ENTRANCE TO ROOM-3
	s27_vertex.push_back(v69);
	s27_vertex.push_back(v70);
	s27_vertex.push_back(v68);
	s27_vertex.push_back(v67);

	// ROOM-3
	s28_vertex.push_back(v72);
	s28_vertex.push_back(v73);
	s28_vertex.push_back(v74);
	s28_vertex.push_back(v75);
	s28_vertex.push_back(v71);
	s28_vertex.push_back(v70);
	s28_vertex.push_back(v69);

	// HALLWAY FROM ROOM-3 TO ROOM-4
	s29_vertex.push_back(v74);
	s29_vertex.push_back(v76);
	s29_vertex.push_back(v77);
	s29_vertex.push_back(v75);

	// ROOM-4 (GOAAAL!)
	s30_vertex.push_back(v78);
	s30_vertex.push_back(v79);
	s30_vertex.push_back(v81);
	s30_vertex.push_back(v80);
	s30_vertex.push_back(v77);
	s30_vertex.push_back(v76);


	sector* s1 = factory->createSector(id++, 10.f, 100.f, s1_vertex);
	sector* s2 = factory->createSector(id++, 10.f, 100.f, s2_vertex);
	sector* s3 = factory->createSector(id++, 10.f, 100.f, s3_vertex);
	sector* s4 = factory->createSector(id++, 15.f, 100.f, s4_vertex);
	sector* s5 = factory->createSector(id++, 20.f, 100.f, s5_vertex);
	sector* s6 = factory->createSector(id++, 25.f, 100.f, s6_vertex);
	sector* s7 = factory->createSector(id++, 25.f, 100.f, s7_vertex);
	sector* s8 = factory->createSector(id++, 25.f, 100.f, s8_vertex);
	sector* s9 = factory->createSector(id++, 25.f, 100.f, s9_vertex);
	sector* s10 = factory->createSector(id++, 10.f, 100.f, s10_vertex);
	sector* s11 = factory->createSector(id++, 17.5f, 100.f, s11_vertex);
	sector* s12 = factory->createSector(id++, 25.f, 60.f, s12_vertex);
	sector* s13 = factory->createSector(id++, 25.f, 60.f, s13_vertex);
	sector* s14 = factory->createSector(id++, 25.f, 60.f, s14_vertex);
	sector* s15 = factory->createSector(id++, 25.f, 60.f, s15_vertex);
	sector* s16 = factory->createSector(id++, 25.f, 60.f, s16_vertex);
	sector* s17 = factory->createSector(id++, 25.f, 60.f, s17_vertex);
	sector* s18 = factory->createSector(id++, 25.f, 60.f, s18_vertex);
	sector* s19 = factory->createSector(id++, 25.f, 60.f, s19_vertex);
	sector* s20 = factory->createSector(id++, 25.f, 60.f, s20_vertex);
	sector* s21 = factory->createSector(id++, 25.f, 60.f, s21_vertex);
	sector* s22 = factory->createSector(id++, 25.f, 60.f, s22_vertex);
	sector* s23 = factory->createSector(id++, 25.f, 60.f, s23_vertex);
	sector* s24 = factory->createSector(id++, 25.f, 60.f, s24_vertex);
	sector* s25 = factory->createSector(id++, 25.f, 60.f, s25_vertex);
	sector* s26 = factory->createSector(id++, 25.f, 60.f, s26_vertex);
	sector* s27 = factory->createSector(id++, 25.f, 60.f, s27_vertex);
	sector* s28 = factory->createSector(id++, 25.f, 60.f, s28_vertex);
	sector* s29 = factory->createSector(id++, 25.f, 60.f, s29_vertex);
	sector* s30 = factory->createSector(id++, 25.f, 60.f, s30_vertex);

	static door d1{v19, v20, true}; // "smallest" point first
	s7->addDoor(&d1);
	s12->addDoor(&d1);
	
	static door d2{v21, v22, true}; // "smallest" point first
	s8->addDoor(&d2);
	s13->addDoor(&d2);

	s1->addNeighbour(s3);
	s1->addNeighbour(s4);
	s1->addNeighbour(s5);
	s1->addNeighbour(s7);

	s2->addNeighbour(s3);
	s2->addNeighbour(s4);
	s2->addNeighbour(s5);
	s2->addNeighbour(s8);

	s3->addNeighbour(s1);
	s3->addNeighbour(s2);
	s3->addNeighbour(s4);

	s4->addNeighbour(s1);
	s4->addNeighbour(s2);
	s4->addNeighbour(s3);
	s4->addNeighbour(s5);

	s5->addNeighbour(s1);
	s5->addNeighbour(s2);
	s5->addNeighbour(s4);
	s5->addNeighbour(s6);

	s6->addNeighbour(s5);
	s6->addNeighbour(s7);
	s6->addNeighbour(s8);
	s6->addNeighbour(s10);
	
	s7->addNeighbour(s1);
	s7->addNeighbour(s6);
	s7->addNeighbour(s10);
	s7->addNeighbour(s11);
	s7->addNeighbour(s9);
	s7->addNeighbour(s12);
	
	s8->addNeighbour(s2);
	s8->addNeighbour(s6);
	s8->addNeighbour(s10);
	s8->addNeighbour(s11);
	s8->addNeighbour(s9);
	s8->addNeighbour(s13);
	
	s9->addNeighbour(s7);
	s9->addNeighbour(s8);
	s9->addNeighbour(s11);
	
	s10->addNeighbour(s6);
	s10->addNeighbour(s7);
	s10->addNeighbour(s8);
	s10->addNeighbour(s11);
	
	s11->addNeighbour(s10);
	s11->addNeighbour(s7);
	s11->addNeighbour(s8);
	s11->addNeighbour(s9);

	s12->addNeighbour(s7);
	s12->addNeighbour(s14);

	s13->addNeighbour(s8);
	s13->addNeighbour(s14);

	s14->addNeighbour(s12);
	s14->addNeighbour(s13);
	s14->addNeighbour(s15);

	s15->addNeighbour(s14);
	s15->addNeighbour(s16);

	s16->addNeighbour(s15);
	s16->addNeighbour(s17);

	s17->addNeighbour(s16);
	s17->addNeighbour(s18);

	s18->addNeighbour(s17);
	s18->addNeighbour(s19);

	s19->addNeighbour(s18);
	s19->addNeighbour(s20);

	s20->addNeighbour(s19);
	s20->addNeighbour(s21);

	s21->addNeighbour(s20);
	s21->addNeighbour(s22);

	s22->addNeighbour(s21);
	s22->addNeighbour(s23);

	s23->addNeighbour(s22);
	s23->addNeighbour(s24);

	s24->addNeighbour(s23);
	s24->addNeighbour(s25);

	s25->addNeighbour(s24);
	s25->addNeighbour(s26);

	s26->addNeighbour(s25);
	s26->addNeighbour(s27);

	s27->addNeighbour(s26);
	s27->addNeighbour(s28);

	s28->addNeighbour(s27);
	s28->addNeighbour(s29);

	s29->addNeighbour(s28);
	s29->addNeighbour(s30);

	s30->addNeighbour(s29);

	sectors.push_back(s1);
	sectors.push_back(s2);
	sectors.push_back(s3);
	sectors.push_back(s4);
	sectors.push_back(s5);
	sectors.push_back(s6);
	sectors.push_back(s7);
	sectors.push_back(s8);
	sectors.push_back(s9);
	sectors.push_back(s10);
	sectors.push_back(s11);
	sectors.push_back(s12);
	sectors.push_back(s13);
	sectors.push_back(s14);
	sectors.push_back(s15);
	sectors.push_back(s16);
	sectors.push_back(s17);
	sectors.push_back(s18);
	sectors.push_back(s19);
	sectors.push_back(s20);
	sectors.push_back(s21);
	sectors.push_back(s22);
	sectors.push_back(s23);
	sectors.push_back(s24);
	sectors.push_back(s25);
	sectors.push_back(s26);
	sectors.push_back(s27);
	sectors.push_back(s28);
	sectors.push_back(s29);
	sectors.push_back(s30);


	return sectors;
}


std::vector<sector*> mapmaker::createTestMap(){
	int id = 1;
	std::vector<sector*> sectors;

	vertex v1 = vertex{0, 0};
	vertex v2 = vertex{10, 0};
	vertex v3 = vertex{50, 0};
	vertex v4 = vertex{60, 0};
	vertex v5 = vertex{10, 10};
	vertex v6 = vertex{50, 10};
	vertex v7 = vertex{10, 30};
	vertex v8 = vertex{50, 30};
	vertex v9 = vertex{10, 40};
	vertex v10 = vertex{50, 40};
	vertex v11 = vertex{10, 50};
	vertex v12 = vertex{50, 50}; 
	vertex v13 = vertex{0, 60};
	vertex v14 = vertex{10, 60};
	vertex v15 = vertex{50, 60};
	vertex v16 = vertex{60, 60};
	vertex v17 = vertex{0, 70};
	vertex v18 = vertex{10, 70};
	vertex v19 = vertex{50, 70};
	vertex v20 = vertex{60, 70};
	vertex v21 = vertex{0, 110};
	vertex v22 = vertex{10, 110};
	vertex v23 = vertex{50, 110};
	vertex v24 = vertex{0, 120};
	vertex v25 = vertex{50, 120};
	vertex v26 = vertex{60, 120};

	vertex v27 = vertex{20, 100};
	vertex v28 = vertex{40, 100};
	vertex v29 = vertex{20, 110};
	vertex v30 = vertex{40, 110};
	vertex v31 = vertex{10, 100};
	vertex v32 = vertex{50, 100};

	static sector s1{id++, 10.f, 80.f}, 
				  s2{id++, 10.f, 80.f},
				  s3{id++, 10.f, 80.f},
				  s4{id++, 15.f, 100.f},
				  s5{id++, 20.f, 100.f},
				  s6{id++, 25.f, 100.f},
				  s7{id++, 30.f, 100.f},

				  s8{id++, 35.f, 100.f},
				  //s9{id++, 10.f, 30.f},
				  
				  s10{id++, 35.f, 90.f},
				  //s11{id++, 10.f, 30.f},
				  
				  s12{id++, 35.f, 90.f},
				  //s13{id++, 10.f, 30.f},

				  //s14{id++, 10.f, 110.f},
				  
				  s15{id++, 35.f, 100.f},
				  //s16{id++, 10.f, 30.f},
				  
				  s17{id++, 35.f, 100.f},
				  //s18{id++, 10.f, 30.f},
				  
				  s19{id++, 35.f, 100.f},
				  //s20{id++, 10.f, 30.f},

				  s21{id++, 22.5f, 100.f},
				  s22{id++, 10.f, 100.f},
				  s23{id++, 10.f, 100.f},
				  s24{id++, 10.f, 100.f};

	s1.addVertex(v1);
	s1.addVertex(v2);
	s1.addVertex(v5);
	s1.addVertex(v7);
	s1.addVertex(v9);
	s1.addVertex(v11);
	s1.addVertex(v14);
	s1.addVertex(v13);


	s2.addVertex(v2);
	s2.addVertex(v3);
	s2.addVertex(v6);
	s2.addVertex(v5);
	

	s3.addVertex(v3);
	s3.addVertex(v4);
	s3.addVertex(v16);
	s3.addVertex(v15);
	s3.addVertex(v12);
	s3.addVertex(v10);
	s3.addVertex(v8);
	s3.addVertex(v6);


	s4.addVertex(v5);
	s4.addVertex(v6);
	s4.addVertex(v7);

	s5.addVertex(v6);
	s5.addVertex(v8);
	s5.addVertex(v7);
	
	s6.addVertex(v7);
	s6.addVertex(v8);
	s6.addVertex(v10);
	s6.addVertex(v9);
	
	s7.addVertex(v9);
	s7.addVertex(v10);
	s7.addVertex(v12);
	s7.addVertex(v11);
	

	s8.addVertex(v11);
	s8.addVertex(v12);
	s8.addVertex(v15);
	s8.addVertex(v19);
	s8.addVertex(v18);
	s8.addVertex(v14);
	/*
	s9.addVertex(v11);
	s9.addVertex(v12);
	s9.addVertex(v15);
	s9.addVertex(v19);
	s9.addVertex(v18);
	s9.addVertex(v14);

*/
	s10.addVertex(v13);
	s10.addVertex(v14);
	s10.addVertex(v18);
	s10.addVertex(v17);
	/*
	s11.addVertex(v13);
	s11.addVertex(v14);
	s11.addVertex(v18);
	s11.addVertex(v17);
*/

	s12.addVertex(v15);
	s12.addVertex(v16);
	s12.addVertex(v20);
	s12.addVertex(v19);
	/*
	s13.addVertex(v15);
	s13.addVertex(v16);
	s13.addVertex(v20);
	s13.addVertex(v19);
*/
/*
	s14.addVertex(v18);
	s14.addVertex(v19);
	s14.addVertex(v23);
	s14.addVertex(v22);
	*/
	
	s15.addVertex(v17);
	s15.addVertex(v18);
	s15.addVertex(v31);
	s15.addVertex(v22);
	s15.addVertex(v21);
	/*
	s16.addVertex(v17);
	s16.addVertex(v18);
	s16.addVertex(v31);
	s16.addVertex(v22);
	s16.addVertex(v21);
	*/

	s17.addVertex(v19);
	s17.addVertex(v20);
	s17.addVertex(v26);
	s17.addVertex(v25);
	s17.addVertex(v23);
	s17.addVertex(v32);
/*
	s18.addVertex(v19);
	s18.addVertex(v20);
	s18.addVertex(v26);
	s18.addVertex(v25);
	s18.addVertex(v23);
	s18.addVertex(v32);
*/
	s19.addVertex(v21);
	s19.addVertex(v22);
	s19.addVertex(v23);
	s19.addVertex(v25);
	s19.addVertex(v24);
	/*
	s20.addVertex(v21);
	s20.addVertex(v22);
	s20.addVertex(v29);
	s20.addVertex(v30);
	s20.addVertex(v23);
	s20.addVertex(v25);
	s20.addVertex(v24);
*/
	s21.addVertex(v27);
	s21.addVertex(v28);
	s21.addVertex(v30);
	s21.addVertex(v29);

	s22.addVertex(v31);
	s22.addVertex(v27);
	s22.addVertex(v29);	 
	s22.addVertex(v22); 

	s23.addVertex(v28);
	s23.addVertex(v32);
	s23.addVertex(v23);	 
	s23.addVertex(v30); 

	s24.addVertex(v18);
	s24.addVertex(v19);
	s24.addVertex(v32);	 
	s24.addVertex(v23);
	s24.addVertex(v30);
	s24.addVertex(v29);
	s24.addVertex(v22);
	s24.addVertex(v31); 


	s1.addNeighbour(&s2);
	s1.addNeighbour(&s4);
	s1.addNeighbour(&s5);
	s1.addNeighbour(&s6);
	s1.addNeighbour(&s7);
	s1.addNeighbour(&s8);
	//s1.addNeighbour(&s9);
	s1.addNeighbour(&s10);
	//s1.addNeighbour(&s11);
	

	s2.addNeighbour(&s1);
	s2.addNeighbour(&s4);
	s2.addNeighbour(&s3);
	
	s3.addNeighbour(&s2);
	s3.addNeighbour(&s5);
	s3.addNeighbour(&s6);
	s3.addNeighbour(&s7);
	s3.addNeighbour(&s8);
	//s3.addNeighbour(&s9);
	s3.addNeighbour(&s12);
	//s3.addNeighbour(&s13);
	
	s4.addNeighbour(&s1);
	s4.addNeighbour(&s2);
	s4.addNeighbour(&s5);

	s5.addNeighbour(&s3);
	s5.addNeighbour(&s4);
	s5.addNeighbour(&s6);


	s6.addNeighbour(&s1);
	s6.addNeighbour(&s3);
	s6.addNeighbour(&s5);
	s6.addNeighbour(&s7);

	s7.addNeighbour(&s1);
	s7.addNeighbour(&s3);
	s7.addNeighbour(&s6);
	s7.addNeighbour(&s8);

	s8.addNeighbour(&s1);
	s8.addNeighbour(&s3);
	s8.addNeighbour(&s7);
	s8.addNeighbour(&s10);
	s8.addNeighbour(&s12);
	s8.addNeighbour(&s24);
/*
	s9.addNeighbour(&s1);
	s9.addNeighbour(&s3);
	s9.addNeighbour(&s7);
	//s9.addNeighbour(&s11);
	//s9.addNeighbour(&s13);
	s9.addNeighbour(&s24);
	*/
	s10.addNeighbour(&s1);
	s10.addNeighbour(&s8);
	s10.addNeighbour(&s15);
	/*
	s11.addNeighbour(&s1);
	s11.addNeighbour(&s9);
	s11.addNeighbour(&s16);
*/
	s12.addNeighbour(&s3);
	s12.addNeighbour(&s8);
	s12.addNeighbour(&s17);
/*
	s13.addNeighbour(&s3);
	s13.addNeighbour(&s9);
	s13.addNeighbour(&s18);
*/
	/*
	s14.addNeighbour(&s8);
	//s14.addNeighbour(&s9);
	s14.addNeighbour(&s15);
	//s14.addNeighbour(&s16);
	s14.addNeighbour(&s17);
	//s14.addNeighbour(&s18);
	s14.addNeighbour(&s19);
	//s14.addNeighbour(&s20);
*/

	s15.addNeighbour(&s10);
	s15.addNeighbour(&s22);
	s15.addNeighbour(&s24);
	s15.addNeighbour(&s19);
/*
	s16.addNeighbour(&s11);
	s16.addNeighbour(&s14);
	s16.addNeighbour(&s20);

*/
	s17.addNeighbour(&s12);
	s17.addNeighbour(&s23);
	s17.addNeighbour(&s24);
	s17.addNeighbour(&s19);
/*
	s18.addNeighbour(&s13);
	s18.addNeighbour(&s14);
	s18.addNeighbour(&s20);
*/

	s19.addNeighbour(&s15);
	s19.addNeighbour(&s21);
	s19.addNeighbour(&s22);
	s19.addNeighbour(&s23);
	s19.addNeighbour(&s17);
/*
	s20.addNeighbour(&s16);
	s20.addNeighbour(&s14);
	s20.addNeighbour(&s18);
	*/

	s21.addNeighbour(&s19);
	s21.addNeighbour(&s22);
	s21.addNeighbour(&s23);
	s21.addNeighbour(&s24);

	s22.addNeighbour(&s15);
	s22.addNeighbour(&s19);
	s22.addNeighbour(&s21);
	s22.addNeighbour(&s24);

	s23.addNeighbour(&s17);
	s23.addNeighbour(&s19);
	s23.addNeighbour(&s21);
	s23.addNeighbour(&s24);

	s24.addNeighbour(&s8);
	s24.addNeighbour(&s15);
	s24.addNeighbour(&s17);
	s24.addNeighbour(&s22);
	s24.addNeighbour(&s21);
	s24.addNeighbour(&s23);


	sectors.push_back(&s1);
	sectors.push_back(&s2);
	sectors.push_back(&s3);
	sectors.push_back(&s4);
	sectors.push_back(&s5);
	sectors.push_back(&s6);
	sectors.push_back(&s7);
	sectors.push_back(&s8);
	//sectors.push_back(&s9);
	sectors.push_back(&s10);
	//sectors.push_back(&s11);
	sectors.push_back(&s12);
	//sectors.push_back(&s13);
	//sectors.push_back(&s14);
	sectors.push_back(&s15);
	//sectors.push_back(&s16);
	sectors.push_back(&s17);
	//sectors.push_back(&s18);
	sectors.push_back(&s19);
	//sectors.push_back(&s20);
	sectors.push_back(&s21);
	sectors.push_back(&s22);
	sectors.push_back(&s23);
	sectors.push_back(&s24);

	return sectors;
}