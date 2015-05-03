#include "mapmaker.hpp"
#include "abstract_sector_factory.hpp"
#include "normal_sector_factory.hpp"

/**
 *	To create a map, you'll need to:
 *	- Create vertex
 *	- Create sector
 *	- Add vertex to sector
 *	- Add neighbours to sector
 *	- Add any doors to sector
 *	- Add sector to vector
 */

// First test-map
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

	sector* s1 = factory->createSector(id++, 10.f, 40.f, s1_vertex, 0);
	sector* s2 = factory->createSector(id++, 25.f, 45.f, s2_vertex, 0);
	sector* s3 = factory->createSector(id++,  7.f, 35.f, s3_vertex, 0);
	sector* s4 = factory->createSector(id++, 10.f, 30.f, s4_vertex, 0);
	sector* s5 = factory->createSector(id++, 25.f, 45.f, s5_vertex, 0);
	sector* s6 = factory->createSector(id++, 25.f, 45.f, s6_vertex, 0);
	sector* s7 = factory->createSector(id++, 25.f, 45.f, s7_vertex, 0);

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

// The big showcase map
std::vector<sector*> mapmaker::createShowcaseMap(){
	int id = 1;
	std::vector<sector*> sectors;

	AbstractSectorFactory* factory = new NormalSectorFactory();
	
	// Create vertecies
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

	vertex v182 = vertex{60, 0};
	vertex v183 = vertex{75, 0};
	vertex v184 = vertex{90, 0};
	vertex v185 = vertex{90, 40};
	vertex v186 = vertex{75, 40};
	vertex v187 = vertex{70, 40};
	vertex v188 = vertex{70, 0};

	// Obstacle in sector 16-hallway
	vertex v82 = vertex{30, 150};
	vertex v83 = vertex{40, 150};
	vertex v84 = vertex{30, 160};
	vertex v85 = vertex{40, 160};

	// Obstacle-1 in sector 21-hallway
	vertex v86 = vertex{100, 160};
	vertex v87 = vertex{110, 160};
	vertex v88 = vertex{120, 160};
	vertex v89 = vertex{100, 150};
	vertex v90 = vertex{110, 150};
	vertex v91 = vertex{120, 150};
	// Obstacle-2 in sector 21-hallway
	vertex v92 = vertex{100, 130};
	vertex v93 = vertex{110, 130};
	vertex v94 = vertex{120, 130};
	vertex v95 = vertex{110, 110};
	vertex v96 = vertex{120, 110};

	// Obstacle in sector 23
	vertex v97 = vertex{50, 90};
	vertex v98 = vertex{70, 90};
	vertex v99 = vertex{50, 100};
	vertex v100 = vertex{70, 100};

	// Create vertex-vector for each sector
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
	std::vector<vertex> s131_vertex;
	std::vector<vertex> s132_vertex;
	std::vector<vertex> s133_vertex;

	std::vector<vertex> s31_vertex;
	std::vector<vertex> s32_vertex;

	std::vector<vertex> s33_vertex;
	std::vector<vertex> s34_vertex;
	std::vector<vertex> s35_vertex;
	std::vector<vertex> s36_vertex;
	std::vector<vertex> s37_vertex;
	std::vector<vertex> s38_vertex;

	std::vector<vertex> s39_vertex;
	std::vector<vertex> s40_vertex;
	std::vector<vertex> s41_vertex;



	// Add vertecies to each sector

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

	// HALLWAY-4-1
	s16_vertex.push_back(v30);
	s16_vertex.push_back(v82);
	s16_vertex.push_back(v84);
	s16_vertex.push_back(v32);

	// HALLWAY-4-OBSTACLE
	s31_vertex.push_back(v82);
	s31_vertex.push_back(v83);
	s31_vertex.push_back(v85);
	s31_vertex.push_back(v84);
	
	// HALLWAY-4-2
	s32_vertex.push_back(v83);
	s32_vertex.push_back(v44);
	s32_vertex.push_back(v41);
	s32_vertex.push_back(v36);
	s32_vertex.push_back(v85);


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
	s21_vertex.push_back(v92);
	s21_vertex.push_back(v93);
	s21_vertex.push_back(v94);
	s21_vertex.push_back(v91);
	s21_vertex.push_back(v90);
	s21_vertex.push_back(v89);

	// HALLWAY-9 OBSTACLE-1
	s37_vertex.push_back(v86);
	s37_vertex.push_back(v87);
	s37_vertex.push_back(v88);
	s37_vertex.push_back(v47);
	s37_vertex.push_back(v46);
	s37_vertex.push_back(v48);

	// HALLWAY-9 OBSTACLE-1
	s35_vertex.push_back(v89);
	s35_vertex.push_back(v90);
	s35_vertex.push_back(v87);
	s35_vertex.push_back(v86);

	// HALLWAY-9 OBSTACLE-1
	s33_vertex.push_back(v90);
	s33_vertex.push_back(v91);
	s33_vertex.push_back(v88);
	s33_vertex.push_back(v87);

	// HALLWAY-9 OBSTACLE-2
	s34_vertex.push_back(v49);
	s34_vertex.push_back(v95);
	s34_vertex.push_back(v93);
	s34_vertex.push_back(v92);

	// HALLWAY-9 OBSTACLE-2
	s36_vertex.push_back(v95);
	s36_vertex.push_back(v96);
	s36_vertex.push_back(v94);
	s36_vertex.push_back(v93);

	// HALLWAY-9 OBSTACLE-2
	s38_vertex.push_back(v50);
	s38_vertex.push_back(v51);
	s38_vertex.push_back(v96);
	s38_vertex.push_back(v95);
	s38_vertex.push_back(v49);


	// HALLWAY-10
	s22_vertex.push_back(v53);
	s22_vertex.push_back(v50);
	s22_vertex.push_back(v49);
	s22_vertex.push_back(v52);

	// ROOM-2
	s23_vertex.push_back(v99);
	s23_vertex.push_back(v100);
	s23_vertex.push_back(v53);
	s23_vertex.push_back(v52);
	s23_vertex.push_back(v55);
	s23_vertex.push_back(v54);
	
	// ROOM-2 - OBSTACLE
	s39_vertex.push_back(v97);
	s39_vertex.push_back(v98);
	s39_vertex.push_back(v100);
	s39_vertex.push_back(v99);

	// ROOM-2 - OBSTACLE
	s40_vertex.push_back(v98);
	s40_vertex.push_back(v59);
	s40_vertex.push_back(v53);
	s40_vertex.push_back(v100);

	// ROOM-2 - OBSTACLE
	s41_vertex.push_back(v56);
	s41_vertex.push_back(v57);
	s41_vertex.push_back(v58);
	s41_vertex.push_back(v59);
	s41_vertex.push_back(v98);
	s41_vertex.push_back(v97);

	
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
	s28_vertex.push_back(v188);
	s28_vertex.push_back(v187);
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

	//Fallpitt in room 28-stairs
	s133_vertex.push_back(v188);
	s133_vertex.push_back(v183);
	s133_vertex.push_back(v186);
	s133_vertex.push_back(v187);

	//Deep pitt, rom 28
	s132_vertex.push_back(v183);
	s132_vertex.push_back(v184);
	s132_vertex.push_back(v185);
	s132_vertex.push_back(v186);

	//platform 2, room 28
	s131_vertex.push_back(v184);
	s131_vertex.push_back(v73);
	s131_vertex.push_back(v74);
	s131_vertex.push_back(v75);
	s131_vertex.push_back(v71);
	s131_vertex.push_back(v185);


	// Create each sector
	sector* s1 = factory->createSector(id++, 10.f, 100.f, s1_vertex, 0);
	sector* s2 = factory->createSector(id++, 10.f, 100.f, s2_vertex, 0);
	sector* s3 = factory->createSector(id++, 10.f, 100.f, s3_vertex, 0);
	sector* s4 = factory->createSector(id++, 15.f, 100.f, s4_vertex, 0);
	sector* s5 = factory->createSector(id++, 20.f, 100.f, s5_vertex, 0);
	sector* s6 = factory->createSector(id++, 25.f, 100.f, s6_vertex, 0);
	sector* s7 = factory->createSector(id++, 25.f, 100.f, s7_vertex, 0);
	sector* s8 = factory->createSector(id++, 25.f, 100.f, s8_vertex, 0);
	sector* s9 = factory->createSector(id++, 25.f, 100.f, s9_vertex, 0);
	sector* s10 = factory->createSector(id++, 10.f, 100.f, s10_vertex, 0);
	sector* s11 = factory->createSector(id++, 17.5f, 100.f, s11_vertex, 0);
	sector* s12 = factory->createSector(id++, 25.f, 60.f, s12_vertex, 7);
	sector* s13 = factory->createSector(id++, 25.f, 60.f, s13_vertex, 7);
	sector* s14 = factory->createSector(id++, 25.f, 60.f, s14_vertex, 7);
	sector* s15 = factory->createSector(id++, 25.f, 60.f, s15_vertex, 7);
	sector* s16 = factory->createSector(id++, 25.f, 70.f, s16_vertex, 7);
	sector* s17 = factory->createSector(id++, 25.f, 60.f, s17_vertex, 7);
	sector* s18 = factory->createSector(id++, 25.f, 60.f, s18_vertex, 7);
	sector* s19 = factory->createSector(id++, 25.f, 60.f, s19_vertex, 7);
	sector* s20 = factory->createSector(id++, 25.f, 60.f, s20_vertex, 7);
	sector* s21 = factory->createSector(id++, 25.f, 60.f, s21_vertex, 7);
	sector* s22 = factory->createSector(id++, 25.f, 60.f, s22_vertex, 7);
	sector* s23 = factory->createSector(id++, 25.f, 70.f, s23_vertex, 7);
	sector* s24 = factory->createSector(id++, 25.f, 60.f, s24_vertex, 7);
	sector* s25 = factory->createSector(id++, 25.f, 60.f, s25_vertex, 0);
	sector* s26 = factory->createSector(id++, 25.f, 60.f, s26_vertex, 0);
	sector* s27 = factory->createSector(id++, 25.f, 75.f, s27_vertex, 8);
	sector* s28 = factory->createSector(id++, 30.f, 80.f, s28_vertex, 8);
	sector* s29 = factory->createSector(id++, 25.f, 60.f, s29_vertex, 7);
	sector* s30 = factory->createSector(id++, 25.f, 60.f, s30_vertex, 9);
	sector* s31 = factory->createSector(id++, 35.f, 70.f, s31_vertex, 7);
	sector* s32 = factory->createSector(id++, 25.f, 70.f, s32_vertex, 7);
	sector* s33 = factory->createSector(id++, 25.f, 35.f, s33_vertex, 7);
	sector* s34 = factory->createSector(id++, 40.f, 70.f, s34_vertex, 7);
	sector* s35 = factory->createSector(id++, 50.f, 60.f, s35_vertex, 7);
	sector* s36 = factory->createSector(id++, 35.f, 70.f, s36_vertex, 7);
	sector* s37 = factory->createSector(id++, 25.f, 70.f, s37_vertex, 7);
	sector* s38 = factory->createSector(id++, 25.f, 70.f, s38_vertex, 7);
	sector* s39 = factory->createSector(id++, 25.f, 70.f, s39_vertex, 7);
	sector* s40 = factory->createSector(id++, 40.f, 70.f, s40_vertex, 7);
	sector* s41 = factory->createSector(id++, 25.f, 70.f, s41_vertex, 7);

	sector* s133 = factory->createSector(id++, 18.f, 80.f, s133_vertex, 8);
	sector* s132 = factory->createSector(id++, 5.f, 80.f, s132_vertex, 8);
	sector* s131 = factory->createSector(id++, 35.f, 80.f, s131_vertex, 8);
	

	// Add doors
	static door d1{v19, v20, true}; // "smallest" point first
	s7->addDoor(&d1);
	s12->addDoor(&d1);
	
	static door d2{v21, v22, true}; // "smallest" point first
	s8->addDoor(&d2);
	s13->addDoor(&d2);

	static door d3{v67, v68, true}; // "smallest" point first
	s26->addDoor(&d3);
	s27->addDoor(&d3);

	static door d4{v76, v77, true}; // "smallest" point first
	s29->addDoor(&d4);
	s20->addDoor(&d4);


	// Add neighbours for each sector

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
	s16->addNeighbour(s31);

	s17->addNeighbour(s32);
	s17->addNeighbour(s18);

	s18->addNeighbour(s17);
	s18->addNeighbour(s19);

	s19->addNeighbour(s18);
	s19->addNeighbour(s20);

	s20->addNeighbour(s19);
	s20->addNeighbour(s37);

	s21->addNeighbour(s35);
	s21->addNeighbour(s33);
	s21->addNeighbour(s34);
	s21->addNeighbour(s36);

	s22->addNeighbour(s38);
	s22->addNeighbour(s23);

	s23->addNeighbour(s22);
	s23->addNeighbour(s39);
	s23->addNeighbour(s40);

	s24->addNeighbour(s41);
	s24->addNeighbour(s25);

	s25->addNeighbour(s24);
	s25->addNeighbour(s26);

	s26->addNeighbour(s25);
	s26->addNeighbour(s27);

	s27->addNeighbour(s26);
	s27->addNeighbour(s28);

	s28->addNeighbour(s27);
	s28->addNeighbour(s133);//29
	//NEW
	s133->addNeighbour(s28);
	s133->addNeighbour(s132);

	s132->addNeighbour(s133);
	s132->addNeighbour(s131);

	s131->addNeighbour(s132);
	s131->addNeighbour(s29);
	//*****//
	s29->addNeighbour(s131);//28
	s29->addNeighbour(s30);

	s30->addNeighbour(s29);

	s31->addNeighbour(s16);
	s31->addNeighbour(s32);

	s32->addNeighbour(s31);
	s32->addNeighbour(s17);

	s33->addNeighbour(s37);
	//s33->addNeighbour(s35);
	s33->addNeighbour(s21);

	s34->addNeighbour(s21);
	s34->addNeighbour(s36);
	s34->addNeighbour(s38);

	s35->addNeighbour(s37);
	//s35->addNeighbour(s33);
	s35->addNeighbour(s21);

	s36->addNeighbour(s21);
	s36->addNeighbour(s34);
	s36->addNeighbour(s38);

	s37->addNeighbour(s20);
	s37->addNeighbour(s35);
	s37->addNeighbour(s33);

	s38->addNeighbour(s34);
	s38->addNeighbour(s36);
	s38->addNeighbour(s22);


	s39->addNeighbour(s23);
	s39->addNeighbour(s40);
	s39->addNeighbour(s41);

	s40->addNeighbour(s23);
	s40->addNeighbour(s39);
	s40->addNeighbour(s41);

	s41->addNeighbour(s39);
	s41->addNeighbour(s40);
	s41->addNeighbour(s24);

	// Add each sector to the vector<sector*>
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
	sectors.push_back(s133);
	sectors.push_back(s132);
	sectors.push_back(s131);
	sectors.push_back(s29);
	sectors.push_back(s30);
	sectors.push_back(s31);
	sectors.push_back(s32);
	sectors.push_back(s33);
	sectors.push_back(s34);
	sectors.push_back(s35);
	sectors.push_back(s36);
	sectors.push_back(s37);
	sectors.push_back(s38);
	sectors.push_back(s39);
	sectors.push_back(s40);
	sectors.push_back(s41);

	return sectors;
}


std::vector<sector*> mapmaker::createTestMap(){
	
}