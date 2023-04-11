/**
 * @file fmi.h
 * Declarations of the FM Index class and support functions.
 */

#pragma once

#include <string>
#include <vector>
#include <map>

/**
 * The FMI class as defined by a BWT string and support data structures
 */
 
class FMI
{
    public:
        std::string F;
        std::string BWT; 
        std::string alpha; 
        std::vector<int> SA;
        std::vector<std::vector<int>> OT;

        /**
        * FM Index constructor; Given T, creates:
        * a Burrows Wheeler Transform (BWT)
        * a suffix array (SA)
        * an occurence table (OT)
        * @param T The string being preprocessed into an FM Index
        * @param alpha The alphabet we are building our index around
        * @param sr The sample rate for the SA and OT (Optional)
        */
        FMI(std::string T, std::string alpha, int sr = 1);

        ~FMI();


        /**
        * SA constructor; Given T, creates:
        * a suffix array (SA)
        * 
        * @param T The string being preprocessed into a SA
        * Has implicit parameter:
        * sr (FMI.sr), the sample rate for the SA and OT (Optional)
        */
        std::vector<int> buildSA(std::string T);


        /**
        * BWT constructor; Given T, creates:
        * a BWT
        * 
        * @param T The string being preprocessed into a BWT
        */
        std::string buildBWT(std::string T);


        /**
        * OT constructor; Given T, creates:
        * a suffix array (SA)
        * 
        * @param T The string being preprocessed into a Occurrence Table
        * Has two implicit parameters:
        * alpha (FMI.alpha) the index's alphabet (Necessary)
        * sr (FMI.sr), the sample rate for the SA and OT (Optional)
        */
        std::vector<std::vector<int>> buildOT(std::string T);


        /**
        * FM Index Exact Pattern Matching
        * 
        * @param P The string being queried
        * You will have to use the SA, OT, BWT, and alphabet
        * If you use sample rate, this is much harder
        */
        std::vector<int> search(std::string P);


        /**
        * FM Index First Range Search
        * 
        * @param c The character being looked up
        * @param s_rank The starting rank being searched 
        * @param e_rank The ending rank being searched 
        *
        * HINT: You will have to reconstruct F from the BWT or the OT
        */
        std::pair<int, int> get_frange(std::string c, int s_rank, int e_rank);

        /**
        * FM Index Last Range Search
        * 
        * @param c The character being looked up
        * @param s_index The starting index being searched 
        * @param e_index The ending index being searched 
        *
        * HINT: L is the BWT 
        */
        std::pair<int, int> get_lrange(std::string c, int s_index, int e_index);

    protected:
        int sampleRate; 

};

std::vector<std::string> rotate(std::string T);
int findChar(std::string alpha, std::string c);