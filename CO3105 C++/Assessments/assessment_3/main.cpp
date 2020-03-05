/*
 * main.cpp
 *
 *  Created on: Oct 30, 2017
 *      Author: np183
 *      Module: CO7105
 *      Department of Informatics
 *      University of Leicester
 */


#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <exception>
#include "Path.h"
#include "Priority.h"
#include "ModelPriority.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

vector<Path::Direction> convert(const vector<char> v);

class intCont {
public:
	int val_;
	intCont() { val_=0; }
	intCont(int v) { val_=v; }
	friend std::ostream& operator<<(std::ostream& o, intCont& i);
};


int main(int argc, char* argv[]) {
	if (false) {
		Path p;
		p.move(Path::N);
		p.move(Path::N);
		p.move(Path::NE);
		p.move(Path::E);
		p.move(Path::E);
		p.move(Path::SE);
		p.move(Path::S);
		p.move(Path::S);
		p.move(Path::SW);
		p.move(Path::W);
		p.move(Path::NW);
		p.move(Path::N);
		cout << p;
		cout<<"end of Code"<<endl;



	}
	if (true) {
	/*	{
			Path p1;
			Path p2;
			p1.move(Path::E);
			p2.move(Path::NE);
			Path p3 = p1+p2;
			cout << p3;
		}
		{
			vector<char> v1{'N','N','E','S','W'};
			Path p1(convert(v1));
			vector<char> v2{'E','S','W'};
			Path p2(convert(v2));
			Path p3 = p1-p2;
			cout << p3;


			vector<char> v4{'E','N','N'};
			Path p4(convert(v4));
			Path p5 = p3-p4;
			cout << p5;
			Path p6;
			p6.move(Path::W);
			if (p6 != p5) {
				cout << "Something went wrong" << endl;
			}

		}*/

		Path p;

				cout << "\nPath.cpp" << endl;

		//Test 1: Basic settings test
				if((p.minX() == 0) && (p.maxX() == 0) &&
					(p.minY() == 0) && (p.maxY() == 0)){
						cout << "Test 1: Passed" << endl;
				}else{
					cout << "Test 1: Failed -> Something wasn't setup properly" << endl;
				}




				//Test 2: Checking the default values of length() and space()
				if(p.space() == 1){
					if(p.length() == 1){
						cout << "Test 2: Passed" << endl;
					}else{
						cout << "Test 2: Failed -> Length() didn't return the expected value of 1" << endl;
					}
				}else{
					cout << "Test 2: Failed -> Space() didn't return the expected value of 1" << endl;
				}


				//Test 3; Testing visited
				if(p.visited(0,0) == 0){
					cout << "Test 3: Passed" << endl;
				}else{
					cout << "Test 3: Failed -> Visited(0,0) should have returned 0" << endl;
				}
















	}

	if (true) {
/*
		Priority<intCont> p;
		intCont* arr[2];
		p.push_back(arr[0] = new intCont(5),1,2);
		p.push_back(arr[1] = new intCont(6),2,1);

		cout << "The following should be 5 6" << endl;
		for (auto it=p.begin(Priority<intCont>::ONE) ;
			 it != p.end(Priority<intCont>::ONE) ; ++it) {
			cout << " " << it->val_;
		}
		cout << endl;

		cout << "The following should be 6 5" << endl;
		for (auto it=p.begin(Priority<intCont>::TWO) ;
			 it != p.end(Priority<intCont>::TWO) ; ++it) {
			cout << " " << *it;
		}
		cout << endl;

		intCont* p1=p.pop_front(Priority<intCont>::ONE);
		intCont* p2=p.pop_front(Priority<intCont>::TWO);

		if (!p1 || !p2) {
			cout << "One of the pointers is null" << endl;

		} else {
			if (p1->val_==p2->val_) {
				cout << "Both pops returned the same value" << endl;
			}
			if (p1->val_!=5) {
				cout << "First pop returned something other than 5: " << p1->val_ << endl;
			}
			if (p2->val_!=6) {
				cout << "Second pop returned something other than 6: " << p2->val_ << endl;
			}
		}
		delete arr[0];
		delete arr[1];

		*/
		cout << "\nPriority.h" << endl;

		Priority<intCont> p,p2,p4, p26;
		Priority<intCont>* p3 = new Priority<intCont>;
		Priority<intCont>* p5 = new Priority<intCont>;
		p3->push_back(new intCont(5),1,2); //Used for testing later
		Priority<intCont> p3_copy(*p3); //Used for testing later
		Priority<intCont> p6(std::move(*p3)); //Used for testing later

		//Test 1: Basic push_back
		p.push_back(new intCont(5),1,2);
		auto test1_it = p.begin(p.ONE);

		if(test1_it->val_ == 5){
			cout << "Test 1: Passed" << endl;
		}else{
			cout << "Test 1: Failed -> The value was incorrect" << endl;
		}



		//Test 2: Testing both priorities
				p.push_back(new intCont(6),2,1);
				auto test2_it = p.begin(p.TWO);

				if(test2_it->val_ == 6){
					test2_it++; //Moving the iterator to the next positon
					if(test2_it->val_ == 5){
						cout << "Test 2: Passed" << endl;
					}else{
						cout << "Test 2: Failed -> The value was incorrect, maybe the wrong priority?" << endl;
					}
				}else{
					cout << "Test 2: Failed -> The value was incorrect" << endl;
				}


				//Test 3: Testing popping
				intCont* test3_pop = p.pop_front(p.ONE);

				if(test3_pop->val_ == 5){
					cout << "Test 3: Passed" << endl;
				}else{
					cout << "Test 3: Failed -> Popped value was incorrect" << endl;
				}


				//Test 4: Making sure popped from both priorities
				auto test4_it = p.begin(p.TWO);

				if(test4_it->val_ == 6){
					cout << "Test 4: Passed" << endl;
				}else{
					cout << "Test 4: Failed -> The value was incorrect, should be 6" << endl;
				}


				//Test 5: Two numbers with the same priority
						p.push_back(new intCont(7),2,1);

						auto test5_it = p.begin(p.ONE);

						if(test5_it->val_ == 6){
							cout << "Test 5: Passed" << endl;
						}else{
							cout << "Test 5: Failed -> Order of priorities is incorrect" << endl;
						}



						//Test 6: Popping two numbers with the same priority
						intCont* test6_pop = p.pop_front(p.ONE);

						if(test6_pop->val_ == 6){
							cout << "Test 6: Passed" << endl;
						}else{
							cout << "Test 6: Failed -> Wrong number popped" << endl;
						}


						//Test 7: Popping when nothing is present
						intCont* test7_pop = p.pop_front(p.ONE);

						if(test7_pop->val_ == 7){
							//If your code crashed, its because you're not trapping if the array/vector/map is empty
							intCont* test7_pop_error = p.pop_front(p.ONE);
							if(!test7_pop_error){
								cout << "Test 7: Passed" << endl;
							}else{
								cout << "Test 7: Failed -> You somehow return a value even though one isn't present" << endl;
							}
						}else{
							cout << "Test 7: Failed -> Wrong number popped" << endl;
						}


						//Test 8: Pushing number with negative priorities
								p.push_back(new intCont(8),-1,2);
								p.push_back(new intCont(9),1,-2);

								auto test8_it = p.begin(p.ONE);

								if(test8_it->val_ == 8){
									test8_it = p.begin(p.TWO);

									if(test8_it->val_ == 9){
										cout << "Test 8: Passed" << endl;
									}else{
										cout << "Test 8: Failed -> The value was incorrect, should be 9" << endl;
									}
								}else{
									cout << "Test 8: Failed -> The value was incorrect, should be 8" << endl;
								}


								//Test 9: Pushing an array
										intCont* test9_pop_1 = p.pop_front(p.ONE); //Clearing the array/vector/map
										intCont* test9_pop_2 = p.pop_front(p.ONE);



										if(test9_pop_2->val_ == 9){
											intCont* test9_arr[2];
											p.push_back(test9_arr[0] = new intCont(5),1,2);
											p.push_back(test9_arr[1] = new intCont(6),2,1);

											auto test9_it = p.begin(p.ONE);

											if(test9_it->val_ == 5){
												test9_it++;

												if(test9_it->val_ == 6){
													cout << "Test 9: Passed" << endl;
												}else{
													cout << "Test 9: Failed -> Wrong value pushed, should be 6" << endl;
												}
											}else{
												cout << "Test 9: Failed -> Wrong value pushed, should be 5" << endl;
											}
										}else{
											cout << "Test 9: Failed -> array/vector/map is was not emptied properly" << endl;
										}


										//Test 10: Check if the number is in both arrays/vectors/maps
												auto test10_it_one = p.begin(p.ONE);
												auto test10_it_two = p.begin(p.TWO);

												test10_it_two++; //Need to move to the next postion

												if(test10_it_one->val_ == test10_it_two->val_){
													cout << "Test 10: Passed" << endl;
												}else{
													cout << "Test 10: Failed -> The number wasn't in both arrays/vectors/maps" << endl;
												}



												//Test 11: Popping from one array/vector/map should also remove it from the other
												intCont* test11_pop = p.pop_front(p.ONE);

												if(test11_pop->val_ == 5){
													//Looking through the second array/vector/map to see if the number 5 appears
													bool test11_found = false;

													for(auto test11_it = p.begin(p.TWO); test11_it != p.end(p.TWO); test11_it++){
														if(test11_it->val_ == 5){
															test11_found = true;
															break;
														}
													}

													if(!test11_found){
														cout << "Test 11: Passed" << endl;
													}else{
														cout << "Test 11: Failed -> Found the number 5 in the other array/vector/map" << endl;
														cout << "Test 11: More info -> Don't forget to erase the found number from the other array/vector/map as well" << endl;
													}
												}else{
													cout << "Test 11: Failed -> The value was incorrect, should be 5" << endl;
												}

												//Test 13: Checking the copy
												intCont* test13_pop = p.pop_front(p.ONE); //Popped 6 from p

												auto test13_it_first = p.begin(p.ONE);
												auto test13_it_second = p2.begin(p.ONE);

												if(test13_it_first->val_ != test13_it_second->val_){
													cout << "Test 13: Passed" << endl;
												}else{
													cout << "Test 13: Failed -> Did not copy" << endl;
												}


												//Test 14: Testing the copy constructors
												delete p3;
												p3 = nullptr;

												auto test14_it = p3_copy.begin(p.ONE);

												if(test14_it->val_ == 5){
													cout << "Test 14: Passed" << endl;
												}else{
													cout << "Test 14: Failed -> Could not get the number" << endl;
												}


												//Test 15: Basic iterator test
												auto test15_it = p.begin(p.ONE);
												auto test15_it_copy(test15_it);

												if(test15_it->val_ == test15_it_copy->val_){
													cout << "Test 15: Passed" << endl;
												}else{
													cout << "Test 15: Failed -> Did not successfully copy" << endl;
												}


												//Test 16: Testing end
												auto test16_it_begin = p.begin(p.ONE);
												auto test16_it_end = p.end(p.ONE);


												if(test16_it_begin != test16_it_end){
													cout << "Test 16: Passed" << endl;
												}else{
													cout << "Teset 16: Failed -> Either begin() or end() isn't return what it should" << endl;
												}


												//Test 17: More indepth test of begin and end
												intCont* test17_pop = p.pop_front(p.ONE); //Array/Vector/Map is now empty

												auto test17_it_begin = p.begin(p.ONE);
												auto test17_it_end = p.end(p.ONE);

												if(test17_it_begin == test17_it_end){
													cout << "Test 17: Passed" << endl;
												}else{
													cout << "Teset 17: Failed -> Either begin() or end() isn't return what it should" << endl;
												}


												//Test 18: operator*
												p.push_back(new intCont(3),1,2);

												auto test18_it = p.begin(p.ONE);
												intCont temp(3);

												//Converting outout to string to later compare
												//https://stackoverflow.com/questions/3513173/converting-ostream-into-standard-string
												std::ostringstream test18_stream_1;
												test18_stream_1 << *test18_it;
												std::string test18_str_1 =  test18_stream_1.str();

												std::ostringstream test18_stream_2;
												test18_stream_2 << temp;
												std::string test18_str_2 =  test18_stream_2.str();

												if(test18_str_1 == test18_str_2){
													cout << "Test 18: Passed" << endl;
												}else{
													cout << "Test 18: Failed -> Operator* did not return what was expected" << endl;
												}



												//Test 20: operator++(int)
														p.push_back(new intCont(4),2,1);

														auto test20_it = p.begin(p.TWO);

														if(test20_it->val_ == 4){
															auto test20_it_copy = test20_it++; //Main test

															if(test20_it->val_ == 3){
																if(test20_it_copy->val_ == 4){
																	cout << "Test 20: Passed" << endl;
																}else{
																	cout << "Test 20: Failed -> Could be due to the operator++(int)" << endl;
																}
															}else{
																cout << "Test 20: Failed -> The number returned did not match the expected outcome" << endl;
															}
														}else{
															cout << "Test 20: Failed -> The number returned did not match the expected outcome" << endl;
														}


														//Test 21: operator++   -> Not (int)
														auto test21_it = p.begin(p.ONE);

														if(test21_it->val_ == 3){
															auto test21_it_copy = ++test21_it; //Main test

															if(test21_it->val_ == 4){
																if(test21_it_copy->val_ == 4){
																	cout << "Test 21: Passed" << endl;
																}else{
																	cout << "Test 21: Failed -> Could be due to the operator++, not (int)" << endl;
																}
															}else{
																cout << "Test 21: Failed -> The number returned did not match the expected outcome" << endl;
															}
														}else{
															cout << "Test 21: Failed -> The number returned did not match the expected outcome" << endl;
														}


														//Test 22: operator==
														auto test22_it_begin = p.begin(p.ONE);
														auto test22_it_end = p.end(p.ONE);

														test22_it_begin++;
														test22_it_begin++;

														if(test22_it_begin == test22_it_end){
															cout << "Test 22: Passed" << endl;
														}else{
															cout << "Test 22: Failed -> Operator== returned false" << endl;
														}


														//Test 23: operator!=
														auto test23_it_begin = p.begin(p.TWO);
														auto test23_it_end = p.end(p.TWO);


														if(test23_it_begin != test23_it_end){
															test23_it_begin++;
															test23_it_begin++;

															if(!(test23_it_begin != test23_it_end)){
																cout << "Test 23: Passed" << endl;
															}else{
																cout << "Test 23: Failed -> Operator!= return false (They are different when they should be the same)" << endl;
															}
														}else{
															cout << "Test 23: Failed -> Operator!= returned true (They are the same when they shouldn't be)" << endl;
														}

	}

	if (false) {
		ModelPriority p;

		intCont* arr[2];
		p.push_back(arr[0] = new intCont(5),1,2);
		p.push_back(arr[1] = new intCont(6),2,1);

		cout << "The following should be 5 6" << endl;
		for (auto it=p.begin(ModelPriority::ONE) ;
				it != p.end(ModelPriority::ONE) ; ++it) {
			cout << " " << it->val_;
		}
		cout << endl;

		cout << "The following should be 6 5" << endl;
		for (auto it=p.begin(ModelPriority::TWO) ;
				it != p.end(ModelPriority::TWO) ; ++it) {
			cout << " " << *it;
		}
		cout << endl;

		intCont* p1=p.pop_front(ModelPriority::ONE);
		intCont* p2=p.pop_front(ModelPriority::TWO);


		if (!p1 || !p2) {
			cout << "One of the pointers is null" << endl;

		} else {
			if (p1->val_==p2->val_) {
				cout << "Both pops returned the same value" << endl;
			}
			if (p1->val_!=5) {
				cout << "First pop returned something other than 5: " << p1->val_ << endl;
			}
			if (p2->val_!=6) {
				cout << "Second pop returned something other than 6: " << p2->val_ << endl;
			}
		}
		delete arr[0];
		delete arr[1];

	}
	return 0;
}

vector<Path::Direction> convert(const vector<char> v) {
	vector<Path::Direction> res;
	for (auto i=v.begin() ; i != v.end() ; ++i) {
		switch(*i) {
		case 'N':
			res.push_back(Path::N);
			break;
		case 'S':
			res.push_back(Path::S);
			break;
		case 'E':
			res.push_back(Path::E);
			break;
		case 'W':
			res.push_back(Path::W);
			break;
		case 'M':
			res.push_back(Path::NW);
			break;
		case 'O':
			res.push_back(Path::NE);
			break;
		case 'R':
			res.push_back(Path::SW);
			break;
		case 'T':
			res.push_back(Path::SE);
			break;
		default:
			throw std::exception();
		}
	}
	return res;
}


std::ostream& operator<<(std::ostream& o, intCont& i) {
	{
		o << i.val_;
		return o;
	}
}

