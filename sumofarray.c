

#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int rank, size;
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int sum = 0;

    // Initializes the MPI execution environment. The variables argc and argv are pointers to command line arguments.
    MPI_Init(&argc, &argv);

    // Determines the rank of the calling process in a communicator. The rank is an integer value of 0 to n-1, with n being the size of the communicator. This way each process has a unique ID that we can use to communicate messages between processes.
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Gets the number of processes that are associated with a specific communicator. If MPI_COMM_WORLD is used as the communicator, all the processes on the cluster would be used and stored in the variable of size.
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n = sizeof(arr) / sizeof(arr[0]);
    int local_sum = 0;
    for (int i = rank; i < n; i += size)
    {
        local_sum += arr[i];
    }

    /*
    MPI_Reduce takes an array of input elements on each process and returns an array of output elements to the root process. The output elements contain the reduced result. The prototype for MPI_Reduce looks like this:
        MPI_Reduce(
            void* send_data,
            void* recv_data,
            int count,
            MPI_Datatype datatype,
            MPI_Op op,
            int root,
            MPI_Comm communicator)
    The send_data parameter is an array of elements of type datatype that each process wants to reduce. The recv_data is only relevant on the process with a rank of root. The recv_data array contains the reduced result and has a size of sizeof(datatype) * count. The op parameter is the operation that you wish to apply to your data. MPI contains a set of common reduction operations that can be used. Although custom reduction operations can be defined, it is beyond the scope of this lesson. The reduction operations defined by MPI include: MPI_SUM - Sums the elements.
    */
    MPI_Reduce(&local_sum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        printf("Sum of array elements is %d\n", sum);
    }

    //  Terminates the MPI execution environment. The final MPI call that should be made, after it no MPI routines can be called.
    MPI_Finalize();
}

//sudo apt install build-essential

//mpicc sumofarray.c -o sumofarray

//./sumofarray
