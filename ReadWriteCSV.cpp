#include <string>
#include <fstream>
#include <sstream>

int main(){
	std::string str_buf;
	std::string str_conma_buf;
	std::string input_csv_file_path = "./input.csv";
	std::string output_csv_file_path = "./output.csv";
	
	//input csvファイルを開く
	std::ifstream ifs_csv_file(input_csv_file_path);
	//output csvファイルを開く
	std::ofstream ofs_csv_file(output_csv_file_path);
	
	//getline関数で一行ごとに読み込む
	while (getline(ifs, str_buf)){
		//，区切りのデータを読み込むためにistringstream型にする
		std::istringstream i_stream(str_buf);
		//，区切りごとのデータを読み込む
		while (getline(i_stream, str_conma_buf, ',')){
			ofs_csv_file << str_conma_buf << '.';	//書き込み
		}
		ofs_csv_file << std::endl;	//改行
	}
}
