OFstream * filePtr(NULL);

if(Pstream::master())
  {
    filePtr = new OFstream("forceDisp.dat");
    OFstream& forceDispFile = *filePtr;
    forceDispFile << "#Disp(mm)\tForce(N)" << endl;
  }
