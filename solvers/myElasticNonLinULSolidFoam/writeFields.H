if (runTime.outputTime())
  {
    volScalarField epsilonEq
      (
       IOobject
       (
	"epsilonEq",
	runTime.timeName(),
	mesh,
	IOobject::NO_READ,
	IOobject::AUTO_WRITE
	),
       sqrt((2.0/3.0)*magSqr(dev(epsilon)))
       );

    Info<< "Max epsilonEq = " << max(epsilonEq).value()
	<< endl;

    volScalarField sigmaEq
      (
       IOobject
       (
	"sigmaEq",
	runTime.timeName(),
	mesh,
	IOobject::NO_READ,
	IOobject::AUTO_WRITE
	),
       sqrt((3.0/2.0)*magSqr(dev(sigma)))
       );

    Info<< "Max sigmaEq = " << max(sigmaEq).value()
	<< endl;

    const fvPatchList& patches = mesh.boundary();
    forAll(patches, patchi)
    {
        const fvPatch& currPatch = patches[patchi];
        //if (currPatch.isWall())
        {
//            symmTensorField& sigmaw = sigma.boundaryField()[patchi];
            forAll(currPatch, facei)
            {
                label faceCelli = currPatch.faceCells()[facei];
                const symmTensor &sigmaw = sigma[faceCelli];
                vector nw = mesh.Sf().boundaryField()[patchi][facei] / mesh.magSf().boundaryField()[patchi][facei];
		forceAreaDensity.boundaryField()[patchi][facei] = sigmaw & nw;
            }
        }
    }

    runTime.write();
  }
