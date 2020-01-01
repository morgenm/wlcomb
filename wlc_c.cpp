/*
wlc_c
The wordlist combiner.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <cctype> //For upper and lower char conversions

const unsigned int char_map_size = 62;
char char_map[char_map_size] = {
    'a','b','c','d','e','f','g','h','i',
    'j','k','l','m','n','o','p','q','r',
    's','t','u','v','w','x','y','z',
    'A','B','C','D','E','F','G','H','I',
    'J','K','L','M','N','O','P','Q','R',
    'S','T','U','V','W','X','Y','Z',
    '0','1','2','3','4','5','6','7','8',
    '9'
};

void combine_words(std::vector<std::map<char, std::string> > &phrases,
    std::vector<std::string> &combos,
    std::ofstream &wordlist_out)
{
    std::vector<std::map<char,std::string> >::iterator mit = phrases.begin();
    int curr_chunk = 0;
    for(; mit!=phrases.end(); mit++)
    {
        std::cout << "Chunk " << curr_chunk << '\n';
        curr_chunk++;
        std::map<char,std::string> m = *mit;
        for(std::vector<std::string>::iterator cit=combos.begin(); cit!=combos.end(); cit++)
        {
            std::string c = *cit;
            std::string word;
            for(unsigned int i=0; i<c.length(); i++)
            {
                if(m.count(c[i]) != 0)
                    word += m[c[i]];
                else //Don't accept any words with any invalid combos
                {
                    word = "";
                    break;
                }
            }
            if(word.length() > 0)
                wordlist_out << word << '\n';
        }
    }
}

int main(int argc, char *argv[])
{
    //Get arguments. These are passed from python
    std::string combo_list_loc = argv[1];
    std::string phrase_loc = argv[2];
    std::string wordlist_loc = argv[3];

    std::string suffixes_arg = "";
    if(argc==5)
        std::string suffixes_arg = argv[4];

    //Add suffixes to vector
    std::vector<std::string> suffixes;
    std::string s = "";
    for(std::string::iterator sit=suffixes_arg.begin(); sit!=suffixes_arg.end(); sit++)
    {
        if(*sit == ',') //End of current string
        {
            suffixes.push_back(s);
            s = "";
        }

        else if(sit+1 == suffixes_arg.end())
        {
            s += *sit;
            suffixes.push_back(s);
        }
        else
        {
            s += *sit;
        }
    }

    //Get the combo list
    std::vector<std::string> combos;

    std::ifstream combo_list_file(combo_list_loc);
    std::string line;
    while(getline(combo_list_file, line))
    {
        if(line[line.length()-1] == '\n')
            line.erase(line.length()-1);
        combos.push_back(line);
    }
    combo_list_file.close();

    std::cout << "Number of combos in combo list " << combos.size() << '\n';


    //Add upper/lower counterparts to wordlist
    std::ifstream phrase_file(phrase_loc);
    std::vector<std::string> tmp_phrases;
    line = "";
    while(getline(phrase_file, line))
    {
        //Swap
        std::string s = line;
        if(std::isupper(line[0]))
        {
            s[0] = std::tolower(line[0]);
        }
        else if(std::islower(line[0]))
        {
            s[0] = std::toupper(line[0]);
        }
        tmp_phrases.push_back(s);

        //All upper
        std::string upper = "";
        for(std::string::iterator sit = line.begin(); sit!=line.end(); sit++)
        {
            upper += std::toupper(*sit);
        }
        tmp_phrases.push_back(upper);
    }
    phrase_file.close();

    std::ofstream phrase_file_out(phrase_loc);
    for(std::vector<std::string>::iterator it=tmp_phrases.begin(); it!=tmp_phrases.end(); it++)
    {
        phrase_file_out << (std::string)*it << '\n';
    }
    phrase_file_out.close();

    //Get phrases
    std::vector<std::map<char,std::string> > phrases;

    std::cout << "Getting phrases from phrase file.\n";
    phrase_file.open(phrase_loc, std::ios::in);
    int total_phrases;
    line = "";
    for(total_phrases=0; std::getline(phrase_file, line); total_phrases++); //Count total phrases
    std::cout << "Total number of phrases: " << total_phrases << '\n';
    phrase_file.close();

    phrase_file.open(phrase_loc, std::ios::in);
    line = "";
    std::map<char,std::string> m;
    unsigned int char_it = 0; //Get the respective char from the char_map array
    int phrase_counter = 0;
    while(getline(phrase_file, line))
    {
        if(line[line.length()-1] == '\n')
            line.erase(line.length()-1);
        m[char_map[char_it]] = line;
        char_it++;
        if(m.size() == char_map_size)
        {
            phrases.push_back(m);
            m.clear();
            char_it = 0;
        }
        else if(phrase_counter == total_phrases-1){
            phrases.push_back(m);
        }
        phrase_counter++;
    }
    phrase_file.close();

    //Combine words
    std::cout << "Combining words.\n";
    std::ofstream wordlist_out(wordlist_loc);
    combine_words(phrases, combos, wordlist_out);
    wordlist_out.close();

    return 0;
}
