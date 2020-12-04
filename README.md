# 2020_Software_Design_Patterns
2020년도 2학기 가천대학교 소프트웨어학과 소프트웨어구현패턴 수업 팀 프로젝트입니다.

## (1) Setup
- Read a text file provided (conference registrations data).
- Store the data in a struct array.
- Store the data in a linked list.

## (2) Search, Reorganize
- Search for “Choi”
  - in the array (P1-1)
  - in the linked list (P1-2)

- Search for all from Gachon University
  - in the array (P2-1)
  - in the linked list (P2-2)
  
- Sort the data in the array in tag# order (P3-1)

- Create a linked list using the sorted data (P4-1)
  - Sort the data in the array in age group order

- Write the sorted data to a text file (P5-1)

- All “Choi”s canceled registration. Remove the data from 
  - the array (fill the memory) (P6-1)
  - the linked list (P6-2)
  
- One “Paik” registered late. Add the data to
  - the array (sorted by age) (P7-1)
  - the linked list (sorted by tag) (P7-2)
  
- Copy the names of most recent data in the array for transmission to a remote computer
  - Compute the checksum of the original data (using bitwise ExclusiveOR) and attach it to the copy
  - Compute the checksum in the copied data, and compare it against the checksum in the original data
  - Confirm that the two data are the same
  - Most recent data: last 5 data in the array 
  - Write a file with checksum(8-1.txt), Then read the file and compare checksum (P8-1)






프로젝트 참여자
---------------
- 가천대학교 김원종
- 가천대학교 안현진
- 가천대학교 이지헌
- 가천대학교 함건욱
